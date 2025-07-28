#include "ldpch.h"
#include "Material.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Lada::Render {
    Material::Material(const std::shared_ptr<Shader> &shader): m_Shader(shader) {
    }

    void Material::Bind() {
        m_Shader->Bind();
        for (auto &[uniformName, texture]: m_Textures) {
            texture->Bind();
            m_Shader->SetUniform1i(uniformName, 0);
        }
        for (auto &[name, vec4]: m_Vec4Uniforms) {
            m_Shader->SetUniform4f(name, vec4.x, vec4.y, vec4.z, vec4.w);
        }

        const glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
        // const glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);
        const glm::mat4 view = glm::mat4(1.0f);
        const glm::mat4 model = glm::mat4(1.0f)
            // glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.04f, 0.0f))
        // * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.4f, 0.4f))
        ;
        glm::mat4 mvp = proj * view * model;
        // m_Shader->SetUniformMat4f("u_MVP", mvp);
    }

    void Material::SetTexture(const std::string &uniformName, const std::shared_ptr<Texture> &texture) {
        m_Textures[uniformName] = texture;
    }

    void Material::SetVector4(const std::string &name, const glm::vec4 value) {
        m_Vec4Uniforms[name] = value;
    }

    MaterialBuilder::MaterialBuilder(const std::shared_ptr<Shader> &shader) {
        m_Material = std::make_shared<Material>(shader);
    }

    MaterialBuilder::MaterialBuilder(const std::string &shaderFilePath) {
        const auto shader = std::make_shared<Shader>(shaderFilePath);
        m_Material = std::make_shared<Material>(shader);
    }

    MaterialBuilder & MaterialBuilder::WithTexture(const std::string &uniformName,
                                                   const std::shared_ptr<Texture> &texture) {
        m_Material->SetTexture(uniformName, texture);
        return *this;
    }

    MaterialBuilder & MaterialBuilder::WithTexture(const std::string &uniformName, const std::string &filePath) {
        const auto texture = std::make_shared<Texture>(filePath);
        m_Material->SetTexture(uniformName, texture);
        return *this;
    }

    MaterialBuilder & MaterialBuilder::WithVector4(const std::string &name, glm::vec4 value) {
        m_Material->SetVector4(name, value);
        return *this;
    }

    std::shared_ptr<Material> MaterialBuilder::Build() {
        return m_Material;
    }
}
