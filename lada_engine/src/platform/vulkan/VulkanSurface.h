#pragma once

#include <vulkan/vulkan.h>

#include "VulkanInstance.h"
#include "app/Window.h"

namespace Lada {
    class VulkanSurface {
    public:
        VulkanSurface(const std::shared_ptr<VulkanInstance> &instance, const std::shared_ptr<Window> &window);

        ~VulkanSurface();

        [[nodiscard]] VkSurfaceKHR NativeSurface() const { return m_Surface; }

    private:
        VkSurfaceKHR m_Surface;
        std::shared_ptr<VulkanInstance> m_VulkanInstance;
    };
}
