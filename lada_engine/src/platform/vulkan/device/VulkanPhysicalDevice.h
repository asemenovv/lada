#pragma once

#include <vulkan/vulkan_core.h>
#include <memory>

#include "VulkanInstance.h"
#include "VulkanSurface.h"


namespace Lada {
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        [[nodiscard]] bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class VulkanPhysicalDevice {
    public:
        explicit VulkanPhysicalDevice(const VulkanInstance& instance, const VulkanSurface& surface);

        [[nodiscard]] VkPhysicalDevice NativePhysicalDevice() const { return m_PhysicalDevice; }

        QueueFamilyIndices FindQueueFamilies() const;

        SwapChainSupportDetails QuerySwapChainSupport() const;
    private:
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device) const;
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        const VulkanInstance& m_Instance;
        const VulkanSurface& m_Surface;
    };
}
