#include "VulkanContext.h"

namespace Lada {
    VulkanContext::VulkanContext(GLFWwindow *window): m_WindowHandle(window) {
    }

    void VulkanContext::Init() {
        m_VulkanInstance = std::make_unique<VulkanInstance>(true);
    }

    void VulkanContext::SwapBuffers() {
    }
}