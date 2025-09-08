#include "VulkanPhysicalDevice.h"

#include "VulkanExtensionsManager.h"
#include "VulkanSurface.h"
#include "app/Logger.h"

namespace Lada {
    VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanInstance& instance, const VulkanSurface& surface)
        : m_Instance(instance), m_Surface(surface) {
        pickPhysicalDevice();
    }

    QueueFamilyIndices VulkanPhysicalDevice::FindQueueFamilies() const {
        return findQueueFamilies(m_PhysicalDevice);
    }

    SwapChainSupportDetails VulkanPhysicalDevice::QuerySwapChainSupport() const {
        return querySwapChainSupport(m_PhysicalDevice);
    }

    void VulkanPhysicalDevice::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        const VkInstance vkInstance = m_Instance.NativeInstance();
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            LD_CORE_CRITICAL("Failed to find GPUs with Vulkan support!");
            std::exit(1);
        }

        LD_CORE_INFO("Found {0} GPUs", deviceCount);
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                m_PhysicalDevice = device;
                break;
            }
        }

        if (m_PhysicalDevice == VK_NULL_HANDLE) {
            LD_CORE_CRITICAL("Failed to find a suitable GPU!");
            std::exit(1);
        }

        // vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_Properties);
        // LD_CORE_INFO("Physical device: {0}", m_Properties.deviceName);
    }

    bool VulkanPhysicalDevice::isDeviceSuitable(const VkPhysicalDevice device) const {
        const QueueFamilyIndices indices = findQueueFamilies(device);

        const bool extensionsSupported = VulkanExtensionsManager::CheckDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            const SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        // VkPhysicalDeviceFeatures supportedFeatures;
        // vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && swapChainAdequate
        // && supportedFeatures.samplerAnisotropy
        ;
    }

    QueueFamilyIndices VulkanPhysicalDevice::findQueueFamilies(const VkPhysicalDevice device) const {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface.NativeSurface(), &presentSupport);
            if (queueFamily.queueCount > 0 && presentSupport) {
                indices.presentFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
            i++;
        }
        return indices;
    }

    SwapChainSupportDetails VulkanPhysicalDevice::querySwapChainSupport(const VkPhysicalDevice device) const {
        SwapChainSupportDetails details;
        const auto surface = m_Surface.NativeSurface();
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }
        return details;
    }
}
