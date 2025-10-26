#include "VulkanCommandBuffer.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanFramebuffer.h"
#include "platform/vulkan/VulkanGraphicsContext.h"
#include "platform/vulkan/VulkanSwapChain.h"
#include "platform/vulkan/commands/VulkanCommandPool.h"

namespace Lada {
    VulkanCommandBuffer::VulkanCommandBuffer(VulkanGraphicsContext *graphicsContext,
                                             const VulkanCommandPool *pool)
        : m_GraphicsContext(graphicsContext) {
        const VkDevice device = graphicsContext->GetDevice().NativeDevice();

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = pool->GetNativePool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        LD_VK_ASSERT_SUCCESS(vkAllocateCommandBuffers(device, &allocInfo, &m_CommandBuffer),
            "Failed to allocate command buffers");
    }

    void VulkanCommandBuffer::Draw(const uint32_t vertexCount, const uint32_t instanceCount,
        const uint32_t firstVertex, const uint32_t firstInstance) {
        vkCmdDraw(m_CommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }

    void VulkanCommandBuffer::DrawIndexed(const uint32_t indexCount, const uint32_t instanceCount,
        const uint32_t firstIndex, const uint32_t firstVertex, const uint32_t firstInstance) {
        vkCmdDrawIndexed(m_CommandBuffer, indexCount, instanceCount, firstIndex, firstVertex, firstInstance);
    }

    void VulkanCommandBuffer::Reset() {
        LD_VK_ASSERT_SUCCESS(vkResetCommandBuffer(m_CommandBuffer, 0), "Failed to reset command buffer!")
    }

    void VulkanCommandBuffer::Begin(const bool singleTime) {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        if (singleTime) {
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        }
        LD_VK_ASSERT_SUCCESS(vkBeginCommandBuffer(m_CommandBuffer, &beginInfo),
            "Failed to begin recording command buffer!");
    }

    void VulkanCommandBuffer::End() {
        LD_VK_ASSERT_SUCCESS(vkEndCommandBuffer(m_CommandBuffer), "Failed to end command buffer!");
    }
}
