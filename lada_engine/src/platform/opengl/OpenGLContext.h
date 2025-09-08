#pragma once
#include "app/Window.h"
#include "renderer/GraphicsContext.h"

namespace Lada {
    class OpenGLContext final : public GraphicsContext {
    public:
        explicit OpenGLContext(Window& window);
        ~OpenGLContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        Window& m_Window;
    };
}
