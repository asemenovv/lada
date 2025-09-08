#include "VulkanGraphicsContext.h"

#include "VulkanSwapChain.h"

namespace Lada {
    VulkanGraphicsContext::VulkanGraphicsContext(const std::shared_ptr<Window>& window): m_Window(window) {
    }

    VulkanGraphicsContext::~VulkanGraphicsContext() {
    }

    void VulkanGraphicsContext::Init() {
        bool enableValidationLayers = true;
        const auto [width, height] = m_Window->GetPixelsSize();
        auto extent = VkExtent2D(width, height);
        m_VulkanInstance = std::make_unique<VulkanInstance>(enableValidationLayers);
        m_Surface = std::make_unique<VulkanSurface>(*m_VulkanInstance, m_Window);
        m_PhysicalDevice = std::make_unique<VulkanPhysicalDevice>(*m_VulkanInstance, *m_Surface);
        m_Device = std::make_unique<VulkanDevice>(*m_VulkanInstance, *m_PhysicalDevice, enableValidationLayers);
        m_SwapChain = std::make_unique<VulkanSwapChain>(this, extent);
    }

    void VulkanGraphicsContext::SwapBuffers() {
    }

    void VulkanGraphicsContext::SetDebugName(const uint64_t handle, const VkObjectType type, const char *name) {
        m_Device->SetDebugName(handle, type, name);
    }
}
