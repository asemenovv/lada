#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanSemaphore {
    public:
        explicit VulkanSemaphore(VulkanGraphicsContext* graphicsContext, const std::string &name = "UNNAMED");
        ~VulkanSemaphore();

        VkSemaphore NativeSemaphore() const { return m_Semaphore; }

    private:
        VkSemaphore m_Semaphore;
        VulkanGraphicsContext* m_GraphicsContext;
    };
}
