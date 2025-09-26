#pragma once

#include <vector>

#include "buffers/VulkanImage.h"
#include "renderer/SwapChain.h"
#include "sync/VulkanFence.h"
#include "sync/VulkanSemaphore.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanSwapChain : public SwapChain {
    public:
        VulkanSwapChain(VulkanGraphicsContext* graphicalContext, VkExtent2D windowExtent);
        ~VulkanSwapChain();

        VkExtent2D GetSwapChainExtent() const { return m_SwapChainExtent; }

        VulkanImage& GetImage(const uint32_t imageIndex) { return m_SwapChainImages[imageIndex]; }

        uint32_t GetImageCount() const { return m_SwapChainImages.size(); }

        bool AcquireNextImage(uint32_t *imageIndex) override;

        bool SubmitCommandBuffer(CommandBuffer *commandBuffer, uint32_t *imageIndex) override;

        bool Present(uint32_t *imageIndex) override;
    private:
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats);

        static VkPresentModeKHR chooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;

        VkSwapchainKHR m_SwapChain;
        VkExtent2D m_WindowExtent;
        VulkanGraphicsContext* m_GraphicsContext;

        std::vector<VulkanImage> m_SwapChainImages;
        VkExtent2D m_SwapChainExtent;

        std::unique_ptr<VulkanSemaphore> m_ImageAvailableSemaphore;
        std::unique_ptr<VulkanSemaphore> m_RenderFinishedSemaphore;
        std::unique_ptr<VulkanFence> m_InFlightFence;
    };
}
