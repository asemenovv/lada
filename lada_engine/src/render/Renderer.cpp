#include "Renderer.h"
#include <iostream>

namespace lada::log {
    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, const int line) {
        while (const GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << "): " << function
                << " " << file << ":" << line << std::endl;
            return false;
        }
        return true;
    }
}

namespace lada::render {
    void Renderer::Clear() const {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
        shader.Bind();
        va.Bind();
        ib.Bind();

        GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}