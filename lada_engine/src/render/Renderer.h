#pragma once

#include <csignal>

#include "GL/glew.h"

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GL_CALL(x) log::GLClearError();\
x;\
ASSERT(log::GLLogCall(#x, __FILE__, __LINE__))

namespace lada::log {
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, const int line);
}

namespace lada::render {
    class Renderer {
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    };
}
