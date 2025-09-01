#pragma once

#include <set>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_macos.h>
#include <vulkan/vulkan_beta.h>

#include "app/Logger.h"

namespace Lada {
    struct VulkanExtensions {
        std::vector<std::string> storage;
        std::vector<const char*> c_strings;
    };

    class VulkanExtensionsManager {
    public:
        static VulkanExtensions DeviceExtensions();
        static VulkanExtensions InstanceExtensions(bool enableValidationLayers);

        static bool CheckInstanceExtensionsSupport(bool enableValidationLayers);
        static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    private:
        static bool checkIfAvailable(std::string type, VulkanExtensions requiredExtensions,
                                     std::vector<VkExtensionProperties> supportedExtensions);
    };

    inline VulkanExtensions VulkanExtensionsManager::DeviceExtensions() {
        std::vector<const char*> deviceExtensions;
        deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        VulkanExtensions result;
        for (const auto& ext : deviceExtensions) {
            result.storage.push_back(ext);
        }
        for (const auto& ext : result.storage) {
            result.c_strings.push_back(ext.c_str());
        }
        return result;
    }

    inline VulkanExtensions VulkanExtensionsManager::InstanceExtensions(bool enableValidationLayers) {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::set<std::string> extensionSet;
        for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
            extensionSet.insert(glfwExtensions[i]);
        }

        extensionSet.insert(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
        extensionSet.insert(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        if (enableValidationLayers) {
            extensionSet.insert(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VulkanExtensions result;
        for (const auto& ext : extensionSet) {
            result.storage.push_back(ext);
        }
        for (const auto& ext : result.storage) {
            result.c_strings.push_back(ext.c_str());
        }

        return result;
    }

    inline bool VulkanExtensionsManager::CheckInstanceExtensionsSupport(bool enableValidationLayers) {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
        VulkanExtensions requiredExtensions = InstanceExtensions(enableValidationLayers);
        return checkIfAvailable("INSTANCE", requiredExtensions, availableExtensions);
    }

    inline bool VulkanExtensionsManager::CheckDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
        VulkanExtensions requiredExtensions = DeviceExtensions();
        return checkIfAvailable("DEVICE", requiredExtensions, availableExtensions);
    }

    inline bool VulkanExtensionsManager::checkIfAvailable(std::string type, VulkanExtensions requiredExtensions,
        std::vector<VkExtensionProperties> supportedExtensions) {
        std::ostringstream availableMsg;
        availableMsg << "Available '" << type <<"' extensions:" << std::endl;
        std::unordered_set<std::string> available;
        for (const auto &extension: supportedExtensions) {
            availableMsg << "\t" << extension.extensionName << std::endl;
            available.insert(extension.extensionName);
        }
        LD_CORE_DEBUG(availableMsg.str());

        std::ostringstream requiredMsg;
        requiredMsg << "Required '" << type << "' extensions:" << std::endl;
        for (const auto &required: requiredExtensions.c_strings) {
            requiredMsg << "\t" << required << std::endl;
            if (!available.contains(required)) {
                LD_CORE_DEBUG(requiredMsg.str());
                return false;
            }
        }
        LD_CORE_DEBUG(requiredMsg.str());
        return true;
    }
}
