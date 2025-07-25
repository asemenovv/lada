#include "ldpch.h"
#include "Material.h"

namespace Lada::Render {
    Material::Material(const std::shared_ptr<Shader> &shader): m_Shader(shader) {
    }

    void Material::Bind() {
        m_Shader->Bind();
        if (m_Texture) {
            m_Texture->Bind();
        }
        for (auto &uniform: m_Vec4Uniforms) {
            m_Shader->SetUniform4f(uniform.first, uniform.second.x, uniform.second.y, uniform.second.z,
                                   uniform.second.w);
        }
    }

    void Material::SetTexture(std::shared_ptr<Texture> texture) {
        m_Texture = texture;
    }

    void Material::SetVector4(const std::string &name, const glm::vec4 value) {
        m_Vec4Uniforms[name] = value;
    }
}
