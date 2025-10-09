#include "ldpch.h"
#include "Model.h"

#include "glm/ext/matrix_transform.hpp"

namespace Lada::Render {
    Model::Model(): m_ModelMatrix(glm::mat4(1.0f)) {
    }

    Model::Model(std::shared_ptr<DeprecatedMesh>& mesh, std::shared_ptr<Material>& material): Model() {
        PushMesh(mesh, material);
    }

    void Model::PushMesh(std::shared_ptr<DeprecatedMesh>& mesh, std::shared_ptr<Material>& material) {
        m_SubMeshes.push_back({ mesh, material });
    }

    void Model::BindMaterial(const std::shared_ptr<Material> &material, const glm::mat4 &projectionMatrix,
        const glm::mat4 &viewMatrix) const {
        const glm::mat4 mvp = projectionMatrix * viewMatrix * m_ModelMatrix;
        material->Bind(mvp);
    }

    ModelBuilder::ModelBuilder() {
        m_Model = std::make_shared<Model>();
    }

    ModelBuilder & ModelBuilder::PushMesh(std::shared_ptr<DeprecatedMesh> &mesh, std::shared_ptr<Material> &material) {
        m_Model->PushMesh(mesh, material);
        return *this;
    }

    ModelBuilder & ModelBuilder::Transform(const glm::mat4 &modelMatrix) {
        m_Model->m_ModelMatrix = modelMatrix;
        return *this;
    }

    ModelBuilder & ModelBuilder::DefaultTransformation() {
        m_Model->m_ModelMatrix = glm::mat4(1.0f);
        return *this;
    }

    ModelBuilder & ModelBuilder::Scale(float scale) {
        return Scale(glm::vec3(scale));
    }

    ModelBuilder & ModelBuilder::Scale(const glm::vec3 scale) {
        m_Model->m_ModelMatrix = glm::scale(m_Model->m_ModelMatrix, scale);
        return *this;
    }

    ModelBuilder & ModelBuilder::Translate(const glm::vec3 position) {
        m_Model->m_ModelMatrix = glm::translate(m_Model->m_ModelMatrix, position);
        return *this;
    }

    ModelBuilder & ModelBuilder::Rotate(const glm::vec3 axis, const float angleGrad) {
        m_Model->m_ModelMatrix = glm::rotate(m_Model->m_ModelMatrix, glm::radians(angleGrad), axis);
        return *this;
    }

    std::shared_ptr<Model> ModelBuilder::Build() {
        return m_Model;
    }
}
