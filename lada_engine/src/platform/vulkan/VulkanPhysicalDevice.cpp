#include "VulkanPhysicalDevice.h"

#include "VulkanExtensionsManager.h"
#include "app/Logger.h"

namespace Lada {
    VulkanPhysicalDevice::VulkanPhysicalDevice(const std::shared_ptr<VulkanInstance> &instance)
        : m_Instance(instance) {
        pickPhysicalDevice();
    }

    void VulkanPhysicalDevice::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        const VkInstance vkInstance = m_Instance->VulkanNativeInstance();
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

    bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
        const QueueFamilyIndices indices = findQueueFamilies(device);

        VulkanExtensionsManager::CheckDeviceExtensionSupport(device);

        // bool swapChainAdequate = false;
        // SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
        // swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

        // VkPhysicalDeviceFeatures supportedFeatures;
        // vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

        return indices.isComplete()
        // && swapChainAdequate && supportedFeatures.samplerAnisotropy
        ;
    }

    QueueFamilyIndices VulkanPhysicalDevice::findQueueFamilies(const VkPhysicalDevice device) {
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
            if (indices.isComplete()) {
                break;
            }
            i++;
        }
        return indices;
    }
}
