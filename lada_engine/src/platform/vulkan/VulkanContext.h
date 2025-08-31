#pragma once

#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class VulkanContext final : public GraphicsContext {
    public:
        explicit VulkanContext(GLFWwindow *window);
        ~VulkanContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
        std::shared_ptr<VulkanInstance> m_VulkanInstance;
        std::shared_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
        std::shared_ptr<VulkanDevice> m_Device;
    };
}
