#include "VulkanDevice.h"

#include "VulkanExtensionsManager.h"

namespace Lada {
    VulkanDevice::VulkanDevice(const std::shared_ptr<VulkanPhysicalDevice> &physicalDevice,
                               bool enableValidationLayers) : m_Device(nullptr) {
        const QueueFamilyIndices indices = physicalDevice->FindQueueFamilies();

        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures = {};

        VkDeviceCreateInfo createInfo{};
        const auto deviceExtensions = VulkanExtensionsManager::DeviceExtensions();
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.enabledExtensionCount = deviceExtensions.c_strings.size();
        createInfo.ppEnabledExtensionNames = deviceExtensions.c_strings.data();
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanInstance::ValidationLayers.size());
            createInfo.ppEnabledLayerNames = VulkanInstance::ValidationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        VkPhysicalDevice vkPhysicalDevice = physicalDevice->NativePhysicalDevice();
        LD_VK_ASSERT_SUCCESS(vkCreateDevice(vkPhysicalDevice, &createInfo, nullptr, &m_Device),
                             "Failed to create logical device!");

        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
    }

    VulkanDevice::~VulkanDevice() {
        vkDestroyDevice(m_Device, nullptr);
    }
}
