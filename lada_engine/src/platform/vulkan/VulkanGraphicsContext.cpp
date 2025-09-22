#include "VulkanGraphicsContext.h"

#include "VulkanSwapChain.h"
#include "app/Logger.h"
#include "pipeline/VulkanPipeline.h"
#include "VulkanFramebuffer.h"

namespace Lada {
    VulkanGraphicsContext::VulkanGraphicsContext(Window& window): m_Window(window) {
    }

    VulkanGraphicsContext::~VulkanGraphicsContext() {
    }

    void VulkanGraphicsContext::Init() {
        bool enableValidationLayers = true;
        const auto [width, height] = m_Window.GetPixelsSize();
        auto extent = VkExtent2D(width, height);
        m_VulkanInstance = std::make_unique<VulkanInstance>(enableValidationLayers);
        m_Surface = std::make_unique<VulkanSurface>(*m_VulkanInstance, m_Window);
        m_PhysicalDevice = std::make_unique<VulkanPhysicalDevice>(*m_VulkanInstance, *m_Surface);
        m_Device = std::make_unique<VulkanDevice>(*m_VulkanInstance, *m_PhysicalDevice, enableValidationLayers);
        m_SwapChain = std::make_unique<VulkanSwapChain>(this, extent);
        m_Pipeline = std::make_unique<VulkanPipeline>(this,
            "/Users/alexeysemenov/CLionProjects/lada/assets/shaders/simple_shader.vert.spv",
            "/Users/alexeysemenov/CLionProjects/lada/assets/shaders/simple_shader.frag.spv");
        crateFrameBuffers();
    }

    void VulkanGraphicsContext::crateFrameBuffers() {
        swapChainFramebuffers.resize(m_SwapChain->GetImageCount());
        for (size_t i = 0; i < m_SwapChain->GetImageCount(); i++) {
            VulkanImage& image = m_SwapChain->GetImage(i);
            swapChainFramebuffers[i] = std::make_unique<VulkanFramebuffer>(this, image);
        }
    }

    void VulkanGraphicsContext::SwapBuffers() {
    }

    void VulkanGraphicsContext::SetDebugName(const uint64_t handle, const VkObjectType type, const char *name) {
        m_Device->SetDebugName(handle, type, name);
    }
}
