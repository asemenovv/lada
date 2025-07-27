#pragma once
#include <memory>

#include "Shader.h"
#include "Texture.h"

namespace Lada::Render {
    class Material {
    public:
        explicit Material(const std::shared_ptr<Shader>& shader);

        void Bind();

        void SetTexture(const std::string& uniformName, const std::shared_ptr<Texture>& texture);

        void SetVector4(const std::string &name, glm::vec4 value);

    private:
        std::shared_ptr<Shader> m_Shader;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
        std::unordered_map<std::string, glm::vec4> m_Vec4Uniforms;
    };

    class MaterialBuilder final {
    public:
        explicit MaterialBuilder(const std::shared_ptr<Shader>& shader);

        explicit MaterialBuilder(const std::string& shaderFilePath);

        MaterialBuilder& WithTexture(const std::string& uniformName, const std::shared_ptr<Texture>& texture);

        MaterialBuilder& WithTexture(const std::string& uniformName, const std::string& filePath);

        MaterialBuilder& WithVector4(const std::string& name, glm::vec4 value);

        std::shared_ptr<Material> Build();
    private:
        std::shared_ptr<Material> m_Material;
    };
}
