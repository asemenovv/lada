#pragma once

#include <vulkan/vulkan_core.h>
#include <memory>

#include "VulkanInstance.h"
#include "VulkanSurface.h"


namespace Lada {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        [[nodiscard]] bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class VulkanPhysicalDevice {
    public:
        explicit VulkanPhysicalDevice(const std::shared_ptr<VulkanInstance> &instance,
            const std::shared_ptr<VulkanSurface> &surface);

        [[nodiscard]] VkPhysicalDevice NativePhysicalDevice() const { return m_PhysicalDevice; }

        QueueFamilyIndices FindQueueFamilies() const;
    private:
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device) const;
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        std::shared_ptr<VulkanInstance> m_Instance;
        std::shared_ptr<VulkanSurface> m_Surface;
    };
}
