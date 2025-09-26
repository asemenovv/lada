#pragma once

#include "CommandBuffer.h"

namespace Lada {
    class SwapChain {
    public:
        virtual bool AcquireNextImage(uint32_t *imageIndex) = 0;

        virtual bool SubmitCommandBuffer(CommandBuffer *buffers, uint32_t *imageIndex) = 0;

        virtual bool Present(uint32_t *imageIndex) = 0;
    };
}
