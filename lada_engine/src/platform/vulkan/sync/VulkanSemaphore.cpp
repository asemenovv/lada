#include "VulkanSemaphore.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    VulkanSemaphore::VulkanSemaphore(VulkanGraphicsContext* graphicsContext): m_GraphicsContext(graphicsContext) {
        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        LD_VK_ASSERT_SUCCESS(
            vkCreateSemaphore(m_GraphicsContext->GetDevice().NativeDevice(), &semaphoreInfo, nullptr, &m_Semaphore),
            "Failed to create semaphore!"
        );
    }

    VulkanSemaphore::~VulkanSemaphore() {
        vkDestroySemaphore(m_GraphicsContext->GetDevice().NativeDevice(), m_Semaphore, nullptr);
    }
}
