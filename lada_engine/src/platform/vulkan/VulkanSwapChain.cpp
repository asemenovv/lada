#include "VulkanSwapChain.h"

#include <limits>
#include <algorithm>

#include "VulkanGraphicsContext.h"
#include "app/Logger.h"
#include "device/VulkanPhysicalDevice.h"
#include "GLFW/glfw3.h"

namespace Lada {
    VulkanSwapChain::VulkanSwapChain(VulkanGraphicsContext *graphicalContext, const VkExtent2D windowExtent)
        : m_WindowExtent(windowExtent), m_GraphicsContext(graphicalContext) {
        const std::shared_ptr<VulkanPhysicalDevice> physicalDevice = graphicalContext->GetPhysicalDevice();
        const std::shared_ptr<VulkanSurface> surface = graphicalContext->GetSurface();
        const std::shared_ptr<VulkanDevice> device = graphicalContext->GetDevice();
        const SwapChainSupportDetails swapChainSupport = physicalDevice->QuerySwapChainSupport();

        const VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        const VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.
            maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface->NativeSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const auto [graphicsFamily, presentFamily] = physicalDevice->FindQueueFamilies();
        const uint32_t queueFamilyIndices[] = {graphicsFamily.value(), presentFamily.value()};
        if (graphicsFamily != presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        LD_VK_ASSERT_SUCCESS(vkCreateSwapchainKHR(device->NativeDevice(), &createInfo, nullptr, &m_SwapChain),
            "Failed to create swap chain!");
    }

    VulkanSwapChain::~VulkanSwapChain() {
        const std::shared_ptr<VulkanDevice> device = m_GraphicsContext->GetDevice();
        vkDestroySwapchainKHR(device->NativeDevice(), m_SwapChain, nullptr);
    }

    VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR> &availableFormats) {
        for (const auto &availableFormat: availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace ==
                VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }
        return availableFormats.front();
    }

    VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR> &availablePresentModes) {
        for (const auto &availablePresentMode: availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) const {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }
        VkExtent2D actualExtent = m_WindowExtent;
        actualExtent.width = std::max(
            capabilities.minImageExtent.width,
            std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(
            capabilities.minImageExtent.height,
            std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}
