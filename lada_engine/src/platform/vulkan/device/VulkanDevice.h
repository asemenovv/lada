#pragma once

#include <memory>

#include "VulkanPhysicalDevice.h"

namespace Lada {
    class VulkanDevice {
    public:
        explicit VulkanDevice(const VulkanInstance& instance, const VulkanPhysicalDevice& physicalDevice, bool enableValidationLayers);
        ~VulkanDevice();

        [[nodiscard]] VkDevice NativeDevice() const { return m_Device; }

        void SetDebugName(uint64_t handle, VkObjectType type, const char* name) const;
    private:
        VkDevice m_Device;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        PFN_vkSetDebugUtilsObjectNameEXT m_VkSetDebugUtilsObjectNameEXT = nullptr;
    };
}
