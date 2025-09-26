#pragma once

#include "CommandBuffer.h"

namespace Lada {
    constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    class SwapChain {
    public:
        virtual ~SwapChain() = default;

        virtual bool AcquireNextImage(uint32_t *imageIndex, int frameIndex) = 0;

        virtual bool SubmitCommandBuffer(CommandBuffer *buffers, uint32_t *imageIndex, int frameIndex) = 0;

        virtual bool Present(uint32_t *imageIndex, int frameIndex) = 0;
    };
}
