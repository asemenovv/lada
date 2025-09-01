#include "VulkanContext.h"

namespace Lada {
    VulkanContext::VulkanContext(const std::shared_ptr<Window>& window): m_Window(window) {
    }

    void VulkanContext::Init() {
        bool enableValidationLayers = true;
        m_VulkanInstance = std::make_shared<VulkanInstance>(enableValidationLayers);
        m_Surface = std::make_shared<VulkanSurface>(m_VulkanInstance, m_Window);
        m_PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(m_VulkanInstance, m_Surface);
        m_Device = std::make_shared<VulkanDevice>(m_PhysicalDevice, enableValidationLayers);
    }

    void VulkanContext::SwapBuffers() {
    }
}