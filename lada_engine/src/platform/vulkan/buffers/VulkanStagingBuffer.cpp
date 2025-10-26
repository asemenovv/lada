#include "VulkanStagingBuffer.h"

namespace Lada {
    VulkanStagingBuffer::VulkanStagingBuffer(VulkanGraphicsContext *graphicsContext, const uint64_t instanceSize,
        const uint32_t instanceCount): VulkanBuffer(graphicsContext, instanceSize, instanceCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
    }

    void VulkanStagingBuffer::Map(const uint64_t size, const uint64_t offset) {
        map(size, offset);
    }

    void VulkanStagingBuffer::Unmap() {
        unmap();
    }

    void VulkanStagingBuffer::WriteToBuffer(const void *data, const uint64_t size, const uint64_t offset) const {
        writeToBuffer(data, size, offset);
    }

    void VulkanStagingBuffer::CopyToBuffer(const VulkanBuffer *dstBuffer, const uint64_t size) const {
        copyBuffer(this->GetNativeBuffer(), dstBuffer->GetNativeBuffer(), size);
    }
}
