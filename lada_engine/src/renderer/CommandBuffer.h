#pragma once

#include "RenderPass.h"

namespace Lada {
    class CommandBuffer {
    public:
        virtual ~CommandBuffer() = default;

        virtual void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) = 0;

        virtual void Reset() = 0;

        virtual void Begin() = 0;

        virtual void End() = 0;
    };
}
