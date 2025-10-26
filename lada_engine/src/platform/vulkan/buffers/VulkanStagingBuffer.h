#pragma once
#include "VulkanBuffer.h"
#include "renderer/buffers/IStagingBuffer.h"

namespace Lada {
    class VulkanStagingBuffer final : public IStagingBuffer, public VulkanBuffer {
    public:
        VulkanStagingBuffer(VulkanGraphicsContext *graphicsContext, uint64_t instanceSize,
                            uint32_t instanceCount);

        void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) override;

        void Unmap() override;

        void WriteToBuffer(const void *data, uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) const override;

        void CopyToBuffer(const VulkanBuffer* dstBuffer, uint64_t size = LD_BUFFER_WHOLE_SIZE) const;
    };
}
