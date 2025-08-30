#include "VulkanContext.h"

namespace Lada {
    VulkanContext::VulkanContext(GLFWwindow *window): m_WindowHandle(window) {
    }

    void VulkanContext::Init() {
        m_VulkanInstance = std::make_unique<VulkanInstance>(true);
        m_PhysicalDevice = std::make_unique<VulkanPhysicalDevice>(std::move(m_VulkanInstance));
    }

    void VulkanContext::SwapBuffers() {
    }
}