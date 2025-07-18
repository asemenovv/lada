#pragma once

#include <csignal>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GL_CALL(x) Logger::GLClearError();\
x;\
ASSERT(Logger::GLLogCall(#x, __FILE__, __LINE__))

namespace Lada::Logger {
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, const int line);
}

namespace Lada::Render {
    class Renderer {
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    };
}
