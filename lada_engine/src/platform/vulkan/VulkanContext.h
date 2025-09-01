#pragma once

#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanSurface.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class VulkanContext final : public GraphicsContext {
    public:
        explicit VulkanContext(const std::shared_ptr<Window>& window);
        ~VulkanContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<VulkanInstance> m_VulkanInstance;
        std::shared_ptr<VulkanSurface> m_Surface;
        std::shared_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
        std::shared_ptr<VulkanDevice> m_Device;
    };
}
