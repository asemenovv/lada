#pragma once
#include <vulkan/vulkan_core.h>

#include "VulkanInstance.h"

namespace Lada {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        // uint32_t graphicsFamily = 0;
        // uint32_t presentFamily = 0;
        // bool graphicsFamilyHasValue = false;
        // bool presentFamilyHasValue = false;
        [[nodiscard]] bool isComplete() const {
            return graphicsFamily.has_value()
            // && presentFamily.has_value()
            ;
        }
    };

    class VulkanPhysicalDevice {
    public:
        explicit VulkanPhysicalDevice(const std::shared_ptr<VulkanInstance> &instance);
    private:
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        std::shared_ptr<VulkanInstance> m_Instance;
    };
}
