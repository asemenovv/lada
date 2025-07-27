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
}
