#include "ldpch.h"
#include "Renderer.h"
#include "app/Logger.h"

namespace Lada::Logger {
    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, const int line) {
        while (const GLenum error = glGetError()) {
            LD_CORE_ERROR("[OpenGL Error] ({0}): {1} {2}:{3}", error, function, file, line);
            return false;
        }
        return true;
    }
}

namespace Lada::Render {
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