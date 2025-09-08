#pragma once

#include <vulkan/vulkan.h>

#include "VulkanInstance.h"
#include "app/Window.h"

namespace Lada {
    class VulkanSurface {
    public:
        VulkanSurface(const VulkanInstance& instance, Window& window);

        ~VulkanSurface();

        [[nodiscard]] VkSurfaceKHR NativeSurface() const { return m_Surface; }

    private:
        VkSurfaceKHR m_Surface;
        const VulkanInstance& m_VulkanInstance;
    };
}
