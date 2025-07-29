#pragma once
#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "assets/IAsset.h"

namespace Lada {
    class Material : public IAsset {
    public:
        explicit Material(const std::shared_ptr<Shader>& shader);

        void Bind();

        void SetTexture(const std::string& uniformName, const std::shared_ptr<Texture>& texture);

        void SetVector4(const std::string &name, glm::vec4 value);

        void Bind(const glm::mat4& mvp);

        void SetName(const std::string& name) const { m_Name = name; }

        std::string& GetName() const { return m_Name; }

    private:
        std::string& m_Name;
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
