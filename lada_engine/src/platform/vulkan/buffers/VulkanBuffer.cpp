#include "VulkanBuffer.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"
#include "renderer/buffers/IVertexBuffer.h"

namespace Lada {
    VulkanBuffer::VulkanBuffer(VulkanGraphicsContext *graphicsContext, const uint64_t instanceSize, const uint32_t instanceCount,
        const VkBufferUsageFlags usageFlags, const VkMemoryPropertyFlags memoryPropertyFlags, const VkDeviceSize minOffsetAlignment)
        : m_Buffer(nullptr), m_GraphicsContext(graphicsContext), m_Usage(usageFlags), m_InstanceSize(instanceSize) {
        m_AlignmentSize = getAlignment(instanceSize, minOffsetAlignment);
        m_BufferSize = instanceCount * m_AlignmentSize;
        const auto device = m_GraphicsContext->GetDevice().NativeDevice();

        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = m_BufferSize;
        bufferInfo.usage = m_Usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        LD_VK_ASSERT_SUCCESS(vkCreateBuffer(device, &bufferInfo, nullptr, &m_Buffer),
                             "Failed to create vertex buffer!");

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, m_Buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = m_GraphicsContext->GetPhysicalDevice().FindMemoryType(
            memRequirements.memoryTypeBits, memoryPropertyFlags);
        LD_VK_ASSERT_SUCCESS(vkAllocateMemory(device, &allocInfo, nullptr, &m_BufferMemory),
                             "Failed to allocate buffer memory!");

        vkBindBufferMemory(device, m_Buffer, m_BufferMemory, 0);
    }

    VulkanBuffer::~VulkanBuffer() {
        unmap();
        vkDestroyBuffer(m_GraphicsContext->GetDevice().NativeDevice(), m_Buffer, nullptr);
        vkFreeMemory(m_GraphicsContext->GetDevice().NativeDevice(), m_BufferMemory, nullptr);
    }

    void VulkanBuffer::map(uint64_t size, uint64_t offset) {
        vkMapMemory(m_GraphicsContext->GetDevice().NativeDevice(), m_BufferMemory, offset, size, 0, &m_Mapped);
    }

    void VulkanBuffer::unmap() {
        if (m_Mapped) {
            vkUnmapMemory(m_GraphicsContext->GetDevice().NativeDevice(), m_BufferMemory);
            m_Mapped = nullptr;
        }
    }

    void VulkanBuffer::writeToBuffer(const void *data, VkDeviceSize size, VkDeviceSize offset) const {
        LD_CORE_ASSERT_WITH_ERROR(m_Mapped != nullptr, "Cannot copy to unmapped buffer");
        if (size == LD_BUFFER_WHOLE_SIZE) {
            memcpy(m_Mapped, data, m_BufferSize);
        } else {
            auto memOffset = static_cast<char *>(m_Mapped);
            memOffset += offset;
            memcpy(memOffset, data, size);
        }
    }

    void VulkanBuffer::copyBuffer(const VkBuffer srcBuffer, const VkBuffer dstBuffer, const uint64_t size) const {
        const std::unique_ptr<CommandBuffer> commandBuffer = m_GraphicsContext->CreateCommandBuffer();
        const auto cmdBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer.get());
        commandBuffer->Begin(true);
        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0; // Optional
        copyRegion.dstOffset = 0; // Optional
        if (size == VK_WHOLE_SIZE) {
            copyRegion.size = m_BufferSize;
        } else {
            copyRegion.size = size;
        }
        vkCmdCopyBuffer(cmdBuffer->NativeCommandBuffer(), srcBuffer, dstBuffer, 1, &copyRegion);

        m_GraphicsContext->EndSingleTimeCommands(cmdBuffer, true);
    }

    VkDeviceSize VulkanBuffer::getAlignment(const uint64_t instanceSize, const uint64_t minOffsetAlignment) {
        if (minOffsetAlignment > 0) {
            return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
        }
        return instanceSize;
    }
}
