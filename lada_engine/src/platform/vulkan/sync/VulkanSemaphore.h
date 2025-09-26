#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanSemaphore {
    public:
        explicit VulkanSemaphore(VulkanGraphicsContext* graphicsContext);
        ~VulkanSemaphore();

        VkSemaphore NativeSemaphore() const { return m_Semaphore; }

    private:
        VkSemaphore m_Semaphore;
        VulkanGraphicsContext* m_GraphicsContext;
    };
}
