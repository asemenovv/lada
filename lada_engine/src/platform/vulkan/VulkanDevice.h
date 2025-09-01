#pragma once

#include <memory>

#include "VulkanPhysicalDevice.h"

namespace Lada {
    class VulkanDevice {
    public:
        explicit VulkanDevice(const std::shared_ptr<VulkanPhysicalDevice>& physicalDevice, bool enableValidationLayers);
        ~VulkanDevice();

        [[nodiscard]] VkDevice NativeDevice() const { return m_Device; }
    private:
        VkDevice m_Device;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;
    };
}
