#pragma once

#include "CommandBuffer.h"
#include "Pipeline.h"
#include "SwapChain.h"

namespace Lada {
    class Window;

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;

        virtual void SwapBuffers() = 0;

        virtual Pipeline *GetPipeline() const = 0;

        virtual SwapChain *GetSwapChain() const = 0;

        virtual std::unique_ptr<CommandBuffer> CreateCommandBuffer() = 0;

        virtual void EndSingleTimeCommands(CommandBuffer *commandBuffer, bool singeTime) = 0;

        virtual void WaitIdle() = 0;

        virtual void RecreateSwapChain() = 0;
    };
}
