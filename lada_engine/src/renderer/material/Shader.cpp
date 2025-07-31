#include "ldpch.h"
#include "Shader.h"
#include "app/GlCall.h"
#include "renderer/Renderer.h"
#include "app/Logger.h"

namespace Lada {
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource): m_RendererID(0) {
        m_RendererID = CreateShader(vertexSource, fragmentSource);
    }

    Shader::~Shader() {
        GL_CALL(glDeleteProgram(m_RendererID));
    }

    void Shader::Bind() const {
        GL_CALL(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const {
        GL_CALL(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string &name, const int value) {
        GL_CALL(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string &name, const float value) {
        GL_CALL(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform4f(const std::string &name, const float v0, const float v1,
                              const float v2, const float v3) {
        GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
        GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    int Shader::GetUniformLocation(const std::string &name) {
        if (m_UniformLocationCache.contains(name)) {
            return m_UniformLocationCache[name];
        }

        GL_CALL(const int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1) {
            LD_CORE_WARN("Uniform '{0}' doesn't exist!");
        }
        m_UniformLocationCache[name] = location;
        return location;
    }

    unsigned int Shader::CompileShader(const unsigned int type, const std::string& source) {
        GL_CALL(const unsigned int id = glCreateShader(type));
        const char* src = source.c_str();
        GL_CALL(glShaderSource(id, 1, &src, nullptr));
        GL_CALL(glCompileShader(id));

        int result;
        GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            GL_CALL(glGetShaderInfoLog(id, length, &length, message));
            LD_CORE_ERROR("Failed to compile {0} shader!\n{1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            GL_CALL(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
        GL_CALL(unsigned int program = glCreateProgram());
        const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
        const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
        GL_CALL(glAttachShader(program, vs));
        GL_CALL(glAttachShader(program, fs));
        GL_CALL(glLinkProgram(program));
        GL_CALL(glValidateProgram(program));

        int result;
        GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
            char* message = static_cast<char *>(alloca(length * sizeof(char)));
            GL_CALL(glGetProgramInfoLog(program, length, &length, message));
            LD_CORE_ERROR("Failed to link program.\n{0}", message);
            GL_CALL(glDeleteProgram(program));
            return 0;
        }

        GL_CALL(glDeleteShader(vs));
        GL_CALL(glDeleteShader(fs));

        return program;
    }
}
