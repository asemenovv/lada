#pragma once

#include "IVertexBuffer.h"
#include "renderer/CommandBuffer.h"

namespace Lada {
    class IIndexBuffer {
    public:
        virtual ~IIndexBuffer() = default;

        virtual void Bind(CommandBuffer* commandBuffer) = 0;

        virtual void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) = 0;

        virtual void Unmap() = 0;

        virtual void WriteToBuffer(const void *data, uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) = 0;
    };
}
