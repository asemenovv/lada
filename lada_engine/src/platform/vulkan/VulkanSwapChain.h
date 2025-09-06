#pragma once

#include <vector>

#include "buffers/VulkanImage.h"
#include "renderer/SwapChain.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanSwapChain : public SwapChain {
    public:
        VulkanSwapChain(const std::shared_ptr<VulkanGraphicsContext>& graphicalContext, VkExtent2D windowExtent);
        ~VulkanSwapChain();
    private:
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats);

        static VkPresentModeKHR chooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;

        VkSwapchainKHR m_SwapChain;
        VkExtent2D m_WindowExtent;
        std::shared_ptr<VulkanGraphicsContext> m_GraphicsContext;

        std::vector<VulkanImage> m_SwapChainImages;
        VkExtent2D m_SwapChainExtent;
    };
}
