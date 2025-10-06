#pragma once
#include "renderer/material/Shader.h"
#include "renderer/material/Texture.h"
#include "renderer/material/Material.h"
#include "app/Logger.h"

#include <yaml-cpp/yaml.h>
#include <stb_image.h>
#include <tiny_obj_loader.h>

#include "Mesh.h"

namespace Lada {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class AssetManager {
    public:
        AssetID Register(AssetType type, const std::string &path);

        template<typename T>
        T* Get(AssetID& id);

        static std::string WorkingDir();
    private:
        std::unordered_map<AssetID, std::unique_ptr<Asset>> m_Assets;

        template<typename T>
        static std::unique_ptr<T> LoadInternal(const std::string &path, AssetID& id);

        static ShaderProgramSource ParseShader(const std::string &filepath);
    };

    // template<typename T>
    // AssetID AssetManager::Load(const std::string &path) {
    //     static std::unordered_map<std::string, std::weak_ptr<Asset> > cache;
    //
    //     if (const auto it = cache.find(path); it != cache.end()) {
    //         if (const auto shared = it->second.lock()) {
    //             return std::static_pointer_cast<T>(shared);
    //         }
    //     }
    //     auto asset = LoadInternal<T>(path);
    //     // cache[path] = asset;
    //     return asset;
    // }

    template<>
    inline std::unique_ptr<Mesh> AssetManager::LoadInternal<Mesh>(const std::string &path, AssetID& id) {
        std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(id);

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;
        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
            throw std::runtime_error(warn + err);
        }

        std::unordered_map<Mesh::Vertex, uint32_t, Mesh::VertexHash> uniqueVertices;
        for (const auto &shape : shapes) {
            for (const auto &index : shape.mesh.indices) {
                Mesh::Vertex vertex{};
                if (index.vertex_index >= 0) {
                    vertex.position = {
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]
                    };

                    vertex.color = {
                        attrib.colors[3 * index.vertex_index + 0],
                        attrib.colors[3 * index.vertex_index + 1],
                        attrib.colors[3 * index.vertex_index + 2]
                    };
                }
                if (index.normal_index >= 0) {
                    vertex.normal = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                    };
                }
                if (index.texcoord_index >= 0) {
                    vertex.uv = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        attrib.texcoords[2 * index.texcoord_index + 1]
                    };
                }
                if (!uniqueVertices.contains(vertex)) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(mesh->VerticesCount());
                    mesh->AddVertex(vertex);
                }
                mesh->AddIndex(uniqueVertices[vertex]);
            }
        }
        LD_CORE_DEBUG("Model file {0} loaded successfully. Vertices count: {1}", path, mesh->VerticesCount());
        return mesh;
    }

    // template<>
    // inline std::shared_ptr<Shader> AssetManager::LoadInternal<Shader>(const std::string &path) {
    //     LD_INFO("Loading shader: '{0}'", path);
    //     auto [vertexSource, fragmentSource] = ParseShader(WorkingDir() + path);
    //     return std::make_shared<Shader>(vertexSource, fragmentSource);
    // }

    // template<>
    // inline std::shared_ptr<Texture> AssetManager::LoadInternal<Texture>(const std::string &path) {
    //     unsigned char *localBuffer = nullptr;
    //     int width, height, BPP;
    //     stbi_set_flip_vertically_on_load(1);
    //     const std::string absolutePath = WorkingDir() + path;
    //     localBuffer = stbi_load(absolutePath.c_str(), &width, &height, &BPP, 4);
    //     LD_INFO("Loading texture: '{0}' ({1}x{2})", path, width, height);
    //     auto texture = std::make_shared<Texture>(localBuffer, width, height, BPP);
    //     if (localBuffer) {
    //         stbi_image_free(localBuffer);
    //     }
    //     return texture;
    // }

    // template<>
    // inline std::shared_ptr<Material> AssetManager::LoadInternal<Material>(const std::string &path) {
    //     LD_INFO("Loading material: '{0}'", path);
    //     YAML::Node root = YAML::LoadFile(WorkingDir() + path);
    //     const auto shaderUri = root["program"]["uri"].as<std::string>();
    //     const auto shader = Load<Shader>(shaderUri);
    //     auto material = std::make_shared<Material>(shader);
    //     const auto materialName = root["name"].as<std::string>();
    //     material->SetName(materialName);
    //     if (root["textures"].IsSequence()) {
    //         for (const auto& textureNode : root["textures"]) {
    //             const auto textureName = textureNode["name"].as<std::string>();
    //             const auto variable = textureNode["variable"].as<std::string>();
    //             const auto textureUri = textureNode["uri"].as<std::string>();
    //             auto texture = Load<Texture>(textureUri);
    //             texture->SetName(textureName);
    //             material->SetTexture(variable, texture);
    //         }
    //     }
    //     if (root["uniforms"].IsSequence()) {
    //         for (const auto& uniformNode : root["uniforms"]) {
    //             const auto uniformName = uniformNode["name"].as<std::string>();
    //             const auto variable = uniformNode["variable"].as<std::string>();
    //             if (uniformNode["type"].as<std::string>() == "COLOR") {
    //                 glm::vec4 value;
    //                 const auto val = uniformNode["value"];
    //                 value.r = val[0].as<float>();
    //                 value.g = val[1].as<float>();
    //                 value.b = val[2].as<float>();
    //                 value.a = val[3].as<float>();
    //                 material->SetVector4(variable, value);
    //             } else {
    //                 LD_CORE_ERROR("Unsupported uniform type in material.");
    //             }
    //         }
    //     }
    //     return material;
    // }
}
