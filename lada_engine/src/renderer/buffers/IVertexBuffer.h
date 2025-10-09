#pragma once

#include "renderer/CommandBuffer.h"

namespace Lada {
    #define LD_BUFFER_WHOLE_SIZE (~0ULL)

    class IVertexBuffer {
    public:
        virtual ~IVertexBuffer() = default;

        virtual void Bind(CommandBuffer* commandBuffer) = 0;

        virtual void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) = 0;

        virtual void Unmap() = 0;

        virtual void WriteToBuffer(const void* data, uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) const = 0;
    };
}
