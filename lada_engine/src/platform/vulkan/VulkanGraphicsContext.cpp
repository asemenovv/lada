#include "VulkanGraphicsContext.h"

#include "VulkanSwapChain.h"

namespace Lada {
    VulkanGraphicsContext::VulkanGraphicsContext(const std::shared_ptr<Window>& window): m_Window(window) {
    }

    void VulkanGraphicsContext::Init() {
        bool enableValidationLayers = true;
        const auto [width, height] = m_Window->GetPixelsSize();
        auto extent = VkExtent2D(width, height);
        m_VulkanInstance = std::make_shared<VulkanInstance>(enableValidationLayers);
        m_Surface = std::make_shared<VulkanSurface>(m_VulkanInstance, m_Window);
        m_PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(m_VulkanInstance, m_Surface);
        m_Device = std::make_shared<VulkanDevice>(m_PhysicalDevice, enableValidationLayers);
        auto context = shared_from_this();
        m_SwapChain = std::make_shared<VulkanSwapChain>(context, extent);
    }

    void VulkanGraphicsContext::SwapBuffers() {
    }
}
