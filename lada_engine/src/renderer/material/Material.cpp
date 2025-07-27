#include "ldpch.h"
#include "Material.h"

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
