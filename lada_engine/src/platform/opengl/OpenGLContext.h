#pragma once
#include "app/Window.h"
#include "renderer/GraphicsContext.h"

namespace Lada {
    class OpenGLContext final : public GraphicsContext {
    public:
        explicit OpenGLContext(const std::shared_ptr<Window>& window);
        ~OpenGLContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        std::shared_ptr<Window> m_Window;
    };
}
