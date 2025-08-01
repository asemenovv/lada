#pragma once

#include <string>
#include <unordered_map>

#include "assets/IAsset.h"
#include "glm/glm.hpp"

namespace Lada {
    class Shader : public IAsset {
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    public:
        explicit Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
        int GetUniformLocation(const std::string& name);
    };
}
