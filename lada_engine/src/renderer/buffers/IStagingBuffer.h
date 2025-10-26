#pragma once

#include <cstdint>

#include "IVertexBuffer.h"

namespace Lada {
    class IStagingBuffer {
    public:
        virtual ~IStagingBuffer() = default;

        virtual void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) = 0;

        virtual void Unmap() = 0;

        virtual void WriteToBuffer(const void* data, uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) const = 0;
    };
}
