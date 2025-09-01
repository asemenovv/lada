#include "VulkanSurface.h"

#include "app/Logger.h"

#include <GLFW/glfw3.h>

namespace Lada {
    VulkanSurface::VulkanSurface(const std::shared_ptr<VulkanInstance> &instance,
                                 const std::shared_ptr<Window> &window)
        : m_Surface(VK_NULL_HANDLE), m_VulkanInstance(instance) {
        const auto glfwWindow = static_cast<GLFWwindow *>(window->GetNativeWindow());
        const VkInstance vkInstance = instance->NativeInstance();
        LD_VK_ASSERT_SUCCESS(glfwCreateWindowSurface(vkInstance, glfwWindow, nullptr, &m_Surface),
                             "Failed to create window surface");
    }

    VulkanSurface::~VulkanSurface() {
        vkDestroySurfaceKHR(m_VulkanInstance->NativeInstance(), m_Surface, nullptr);
    }
}
