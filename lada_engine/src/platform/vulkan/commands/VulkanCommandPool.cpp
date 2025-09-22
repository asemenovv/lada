#include "VulkanCommandPool.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"
#include "platform/vulkan/device/VulkanPhysicalDevice.h"

namespace Lada {
    VulkanCommandPool::VulkanCommandPool(VulkanGraphicsContext *graphicsContext)
        : m_GraphicsContext(graphicsContext) {
        const QueueFamilyIndices queueFamilyIndices = m_GraphicsContext->GetPhysicalDevice().FindQueueFamilies();

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        LD_VK_ASSERT_SUCCESS(vkCreateCommandPool(m_GraphicsContext->GetDevice().NativeDevice(), &poolInfo,
            nullptr, &m_CommandPool), "Failed to create command pool!");
    }

    VulkanCommandPool::~VulkanCommandPool() {
        vkDestroyCommandPool(m_GraphicsContext->GetDevice().NativeDevice(), m_CommandPool, nullptr);
    }
}
