#pragma once
#include "renderer/Mesh.h"
#include "renderer/material/Material.h"
#include "renderer/Renderer.h"

namespace Lada::Render {
    class Model {
    public:
        struct SubMesh {
            std::shared_ptr<Mesh> mesh;
            std::shared_ptr<Material> material;
        };

        Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material);
        void PushMesh(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& material);
        void Draw(std::shared_ptr<Renderer> renderer);
    private:
        std::vector<SubMesh> m_SubMeshes;
        glm::mat4 m_ModelMatrix{};
    };
}
