#include "VulkanContext.h"

namespace Lada {
    VulkanContext::VulkanContext(GLFWwindow *window): m_WindowHandle(window) {
    }

    void VulkanContext::Init() {
        bool enableValidationLayers = true;
        m_VulkanInstance = std::make_shared<VulkanInstance>(enableValidationLayers);
        m_PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(m_VulkanInstance);
        m_Device = std::make_shared<VulkanDevice>(m_PhysicalDevice, enableValidationLayers);
    }

    void VulkanContext::SwapBuffers() {
    }
}