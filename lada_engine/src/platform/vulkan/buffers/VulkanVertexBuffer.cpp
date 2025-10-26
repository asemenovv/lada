#include "VulkanVertexBuffer.h"

namespace Lada {
    VulkanVertexBuffer::VulkanVertexBuffer(VulkanGraphicsContext *graphicsContext, const uint64_t instanceSize,
                                           const uint32_t instanceCount, const bool withStaging)
        : VulkanBuffer(
            graphicsContext, instanceSize, instanceCount,
            withStaging
                ? VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                : VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            withStaging
                ? VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                : VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        ) {
    }

    void VulkanVertexBuffer::Bind(CommandBuffer *commandBuffer) {
        const auto vulkanCommandBuffer = reinterpret_cast<VulkanCommandBuffer *>(commandBuffer);
        const VkBuffer buffers[] = {this->GetNativeBuffer()};
        constexpr VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(vulkanCommandBuffer->NativeCommandBuffer(), 0, 1, buffers, offsets);
    }

    void VulkanVertexBuffer::Map(uint64_t size, uint64_t offset) {
        map(size, offset);
    }

    void VulkanVertexBuffer::Unmap() {
        unmap();
    }

    void VulkanVertexBuffer::WriteToBuffer(const void *data, VkDeviceSize size, VkDeviceSize offset) const {
        writeToBuffer(data, size, offset);
    }
}
