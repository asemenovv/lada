#include "ldpch.h"
#include "Model.h"

namespace Lada::Render {
    Model::Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material) {
        PushMesh(mesh, material);
    }

    void Model::PushMesh(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material) {
        m_SubMeshes.push_back({ mesh, material });
    }

    void Model::Draw(std::shared_ptr<Renderer> renderer) {
        for (const auto&[mesh, material] : m_SubMeshes) {
            material->Bind();
            mesh->Draw();
        }
    }
}
