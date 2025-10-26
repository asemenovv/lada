#pragma once

#include <vulkan/vulkan.h>

#include "platform/vulkan/commands/VulkanCommandBuffer.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanBuffer {
    public:
        VulkanBuffer(VulkanGraphicsContext* graphicsContext, uint64_t instanceSize,
                uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
                VkDeviceSize minOffsetAlignment = 1);

        virtual ~VulkanBuffer();

        VkBuffer GetNativeBuffer() const { return m_Buffer; }

    protected:
        void map(uint64_t size = VK_WHOLE_SIZE, uint64_t offset = 0);

        void unmap();

        void writeToBuffer(const void* data, uint64_t size = VK_WHOLE_SIZE, uint64_t offset = 0) const;

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;
    private:
        VkBuffer m_Buffer;
        VkDeviceMemory m_BufferMemory;
        void* m_Mapped = nullptr;
        VulkanGraphicsContext* m_GraphicsContext;
        VkBufferUsageFlags m_Usage;

        VkDeviceSize m_BufferSize;
        VkDeviceSize m_AlignmentSize;
        VkDeviceSize m_InstanceSize;

        static VkDeviceSize getAlignment(uint64_t instanceSize, uint64_t minOffsetAlignment);
    };
}
