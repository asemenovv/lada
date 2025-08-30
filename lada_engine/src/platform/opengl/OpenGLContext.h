#pragma once
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class OpenGLContext final : public GraphicsContext {
    public:
        explicit OpenGLContext(GLFWwindow *window);
        ~OpenGLContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}
