#pragma once
#include "renderer/DeprecatedMesh.h"
#include "renderer/material/Material.h"

namespace Lada::Render {
    class Model {
        friend class ModelBuilder;

    public:
        struct SubMesh {
            std::shared_ptr<DeprecatedMesh> mesh;
            std::shared_ptr<Material> material;
        };

        Model();

        Model(std::shared_ptr<DeprecatedMesh> &mesh, std::shared_ptr<Material> &material);

        void PushMesh(std::shared_ptr<DeprecatedMesh> &mesh, std::shared_ptr<Material> &material);

        std::vector<SubMesh>::iterator begin() { return m_SubMeshes.begin(); }
        std::vector<SubMesh>::iterator end() { return m_SubMeshes.end(); }

        void BindMaterial(const std::shared_ptr<Material> &material, const glm::mat4 &projectionMatrix,
                          const glm::mat4 &viewMatrix) const;

    private:
        std::vector<SubMesh> m_SubMeshes;
        glm::mat4 m_ModelMatrix;
    };

    class ModelBuilder {
    public:
        ModelBuilder();

        ModelBuilder &PushMesh(std::shared_ptr<DeprecatedMesh> &mesh, std::shared_ptr<Material> &material);

        ModelBuilder &Transform(const glm::mat4 &modelMatrix);

        ModelBuilder &DefaultTransformation();

        ModelBuilder &Scale(float scale);

        ModelBuilder &Scale(glm::vec3 scale);

        ModelBuilder &Translate(glm::vec3 position);

        ModelBuilder &Rotate(glm::vec3 axis, float angleGrad);

        std::shared_ptr<Model> Build();

    private:
        std::shared_ptr<Model> m_Model;
    };
}
