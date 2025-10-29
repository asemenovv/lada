#pragma once
#include "IVertexBuffer.h"

namespace Lada {
    class IUniformBuffer {
    public:
        virtual ~IUniformBuffer() = default;

        virtual void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) = 0;

        virtual void Unmap() = 0;

        virtual void WriteToBuffer(const void* data, uint64_t size, uint64_t offset) const = 0;
    };
}
