#include "VulkanIndexBuffer.h"

namespace Lada {
    VulkanIndexBuffer::VulkanIndexBuffer(VulkanGraphicsContext *graphicsContext, const uint64_t instanceSize,
                                         const uint32_t instanceCount, bool withStaging)
        : VulkanBuffer(
            graphicsContext, instanceSize, instanceCount,
            withStaging
                ? VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                : VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            withStaging
                ? VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                : VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
    }

    void VulkanIndexBuffer::Bind(CommandBuffer *commandBuffer) {
        const auto vulkanCommandBuffer = reinterpret_cast<VulkanCommandBuffer *>(commandBuffer);
        vkCmdBindIndexBuffer(vulkanCommandBuffer->NativeCommandBuffer(), GetNativeBuffer(), 0, VK_INDEX_TYPE_UINT32);
    }

    void VulkanIndexBuffer::Map(const uint64_t size, const uint64_t offset) {
        map(size, offset);
    }

    void VulkanIndexBuffer::Unmap() {
        unmap();
    }

    void VulkanIndexBuffer::WriteToBuffer(const void *data, const uint64_t size, const uint64_t offset) {
        writeToBuffer(data, size, offset);
    }
}
