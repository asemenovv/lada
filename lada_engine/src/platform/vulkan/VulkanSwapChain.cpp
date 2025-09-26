#include "VulkanSwapChain.h"

#include <limits>
#include <algorithm>

#include "VulkanGraphicsContext.h"
#include "app/Logger.h"
#include "commands/VulkanCommandBuffer.h"
#include "device/VulkanPhysicalDevice.h"
#include "GLFW/glfw3.h"

namespace Lada {
    VulkanSwapChain::VulkanSwapChain(VulkanGraphicsContext *graphicalContext, const VkExtent2D windowExtent)
        : m_SwapChain(VK_NULL_HANDLE), m_WindowExtent(windowExtent), m_GraphicsContext(graphicalContext),
          m_SwapChainExtent({}) {
        const VulkanPhysicalDevice &physicalDevice = graphicalContext->GetPhysicalDevice();
        const VulkanSurface &surface = graphicalContext->GetSurface();
        const VulkanDevice &device = graphicalContext->GetDevice();
        const SwapChainSupportDetails swapChainSupport = physicalDevice.QuerySwapChainSupport();

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
        createInfo.surface = surface.NativeSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const auto [graphicsFamily, presentFamily] = physicalDevice.FindQueueFamilies();
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

        LD_VK_ASSERT_SUCCESS(vkCreateSwapchainKHR(device.NativeDevice(), &createInfo, nullptr, &m_SwapChain),
                             "Failed to create swap chain!");
        m_GraphicsContext->SetDebugName(reinterpret_cast<uint64_t>(m_SwapChain), VK_OBJECT_TYPE_SWAPCHAIN_KHR,
                                        "SwapChain");

        vkGetSwapchainImagesKHR(device.NativeDevice(), m_SwapChain, &imageCount, nullptr);
        std::vector<VkImage> swapChainImages = {};
        swapChainImages.resize(imageCount);
        m_SwapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device.NativeDevice(), m_SwapChain, &imageCount, swapChainImages.data());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            m_SwapChainImages[i] = VulkanImage(m_GraphicsContext, swapChainImages[i], surfaceFormat.format,
                                               VK_IMAGE_ASPECT_COLOR_BIT, "SwapChainImages[" + std::to_string(i) + "]");
        }
        m_SwapChainExtent = extent;

        m_ImageAvailableSemaphore = std::make_unique<VulkanSemaphore>(graphicalContext);
        m_RenderFinishedSemaphore = std::make_unique<VulkanSemaphore>(graphicalContext);
        m_InFlightFence = std::make_unique<VulkanFence>(graphicalContext, true);
    }

    VulkanSwapChain::~VulkanSwapChain() {
        const VulkanDevice &device = m_GraphicsContext->GetDevice();
        vkDestroySwapchainKHR(device.NativeDevice(), m_SwapChain, nullptr);
    }

    bool VulkanSwapChain::AcquireNextImage(uint32_t *imageIndex) {
        m_InFlightFence->Wait();
        const VkResult result = vkAcquireNextImageKHR(m_GraphicsContext->GetDevice().NativeDevice(), m_SwapChain,
                                                      UINT64_MAX, m_ImageAvailableSemaphore->NativeSemaphore(),
                                                      VK_NULL_HANDLE, imageIndex);
        return result == VK_SUCCESS;
    }

    bool VulkanSwapChain::SubmitCommandBuffer(CommandBuffer *commandBuffer, uint32_t *imageIndex) {
        const VkCommandBuffer vkCommandBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer)->
                NativeCommandBuffer();
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        const VkSemaphore waitSemaphores[] = {m_ImageAvailableSemaphore->NativeSemaphore()};
        constexpr VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &vkCommandBuffer;
        const VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphore->NativeSemaphore()};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
        m_InFlightFence->Reset();
        const VkResult result = vkQueueSubmit(m_GraphicsContext->GetDevice().GraphicsQueue(), 1, &submitInfo,
                                              m_InFlightFence->NativeFence());
        return result == VK_SUCCESS;
    }

    bool VulkanSwapChain::Present(uint32_t *imageIndex) {
        const VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphore->NativeSemaphore()};
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        const VkSwapchainKHR swapChains[] = {m_SwapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = imageIndex;
        presentInfo.pResults = nullptr;
        const VkResult result = vkQueuePresentKHR(m_GraphicsContext->GetDevice().PresentQueue(), &presentInfo);
        return result == VK_SUCCESS;
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
