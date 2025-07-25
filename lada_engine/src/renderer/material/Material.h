#pragma once
#include <memory>

#include "Shader.h"
#include "Texture.h"

namespace Lada::Render {
    class Material {
    public:
        Material(const std::shared_ptr<Shader>& shader);

        void Bind();

        void SetTexture(std::shared_ptr<Texture> texture);

        void SetVector4(const std::string &name, glm::vec4 value);

    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;
        std::unordered_map<std::string, glm::vec4> m_Vec4Uniforms;
    };
}
