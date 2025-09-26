#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanFence {
    public:
        explicit VulkanFence(VulkanGraphicsContext *graphicsContext, const std::string &name = "UNNAMED",
                             bool signaled = false);
        ~VulkanFence();

        void Wait();
        void Reset();

        VkFence NativeFence() const { return m_Fence; }

    private:
        VkFence m_Fence;
        VulkanGraphicsContext* m_GraphicsContext;
    };
}
