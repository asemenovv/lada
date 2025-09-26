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

        Pipeline* GetPipeline() const override { return nullptr; }

        std::unique_ptr<CommandBuffer> CreateCommandBuffer() override { return nullptr; }

        void EndSingleTimeCommands(CommandBuffer *commandBuffer) override {}

        SwapChain* GetSwapChain() const override;

        void WaitIdle() override {};

    private:
        Window& m_Window;
    };
}
