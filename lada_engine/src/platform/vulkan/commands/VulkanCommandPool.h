#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanCommandPool {
    public:
        explicit VulkanCommandPool(VulkanGraphicsContext* graphicsContext);
        ~VulkanCommandPool();

        VkCommandPool GetNativePool() const { return m_CommandPool; }
    private:
        VkCommandPool m_CommandPool;
        VulkanGraphicsContext* m_GraphicsContext;
    };
}
