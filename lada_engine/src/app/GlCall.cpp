#include "ldpch.h"
#include "app/GlCall.h"
#include "renderer/Renderer.h"
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
