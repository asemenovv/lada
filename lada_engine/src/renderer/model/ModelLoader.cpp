#include "ldpch.h"
#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "app/Logger.h"
#include "renderer/Mesh.h"

namespace Lada::Render {
    std::shared_ptr<Mesh> ModelLoader::LoadModel(const std::string &filePath) {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(
            filePath,
            aiProcess_CalcTangentSpace | aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LD_CORE_ERROR("Error loading model from file '{0}'", filePath);
        }
        LD_CORE_INFO("Loaded model '{0}'. Number of meshes: {1}", filePath, scene->mNumMeshes);

        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh *meshBinding = scene->mMeshes[i];

            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            for (unsigned int v = 0; v < meshBinding->mNumVertices; ++v) {
                const aiVector3D& pos = meshBinding->mVertices[v];
                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);

                if (meshBinding->HasNormals()) {
                    const aiVector3D& normal = meshBinding->mNormals[v];
                    vertices.push_back(normal.x);
                    vertices.push_back(normal.y);
                    vertices.push_back(normal.z);
                }

                if (meshBinding->HasTextureCoords(0)) {
                    const aiVector3D& uv = meshBinding->mTextureCoords[0][v];
                    vertices.push_back(uv.x);
                    vertices.push_back(uv.y);
                }
            }

            for (unsigned int f = 0; f < meshBinding->mNumFaces; ++f) {
                aiFace& face = meshBinding->mFaces[f];
                for (unsigned int j = 0; j < face.mNumIndices; ++j)
                    indices.push_back(face.mIndices[j]);
            }

            return MeshBuilder(vertices.data(), vertices.size() * sizeof(float))
            .Indices(indices.data(), indices.size())
            .PushToLayout<float>(3)
            .PushToLayoutIf<float>(meshBinding->HasNormals(), 3)
            .PushToLayoutIf<float>(meshBinding->HasTextureCoords(0), 2)
            .FinalizeBuffer()
            .Build();
        }
    }
}
