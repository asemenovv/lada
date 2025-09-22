#pragma once

#include "CommandBuffer.h"
#include "Pipeline.h"

namespace Lada {
    class Window;

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        virtual Pipeline* GetPipeline() const = 0;
        virtual std::unique_ptr<CommandBuffer> BeginSingleTimeCommands() = 0;
    };
}
