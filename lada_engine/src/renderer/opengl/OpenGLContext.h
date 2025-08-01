#pragma once
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow *window);
        ~OpenGLContext() = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}
