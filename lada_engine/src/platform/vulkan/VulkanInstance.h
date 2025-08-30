#pragma once
#define VK_USE_PLATFORM_MACOS_MVK

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanInstance {
    public:
        explicit VulkanInstance(bool enableValidationLayers);

        ~VulkanInstance();

        [[nodiscard]] VkInstance VulkanNativeInstance() const { return m_Instance; }

    private:
        void createInstance();

        void setupDebugMessenger();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

        static bool checkValidationLayerSupport();

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
        bool m_EnableValidationLayers;
        static const std::vector<const char *> s_ValidationLayers;
    };
}
