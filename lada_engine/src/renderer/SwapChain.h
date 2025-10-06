#pragma once

#include "CommandBuffer.h"
#include "RenderStatus.h"

namespace Lada {
    constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    class SwapChain {
    public:
        struct Extent {
            uint32_t width;
            uint32_t height;

            [[nodiscard]] float AspectRatio() const {
                return static_cast<float>(width) / static_cast<float>(height);
            }
        };

        virtual ~SwapChain() = default;

        virtual RenderStatus AcquireNextImage(uint32_t *imageIndex, int frameIndex) = 0;

        virtual bool SubmitCommandBuffer(CommandBuffer *buffers, uint32_t *imageIndex, int frameIndex) = 0;

        virtual RenderStatus Present(uint32_t *imageIndex, int frameIndex) = 0;

        virtual Extent Extent() = 0;
    };
}
