#include "VulkanUniformBuffer.h"

#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    VulkanUniformBuffer::VulkanUniformBuffer(GraphicsContext *graphicsContext, const uint64_t instanceSize)
        : VulkanBuffer(static_cast<VulkanGraphicsContext*>(graphicsContext), instanceSize, 1, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
    }

    void VulkanUniformBuffer::Map(const uint64_t size, const uint64_t offset) {
        map(size, offset);
    }

    void VulkanUniformBuffer::Unmap() {
        unmap();
    }

    void VulkanUniformBuffer::WriteToBuffer(const void *data, const uint64_t size, const uint64_t offset) const {
        writeToBuffer(data, size, offset);
    }
}
