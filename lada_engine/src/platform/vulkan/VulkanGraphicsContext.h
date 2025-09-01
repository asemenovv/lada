#pragma once

#include "device/VulkanDevice.h"
#include "device/VulkanInstance.h"
#include "device/VulkanPhysicalDevice.h"
#include "device/VulkanSurface.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class VulkanSwapChain;

    class VulkanGraphicsContext final : public GraphicsContext {
    public:
        explicit VulkanGraphicsContext(const std::shared_ptr<Window>& window);
        ~VulkanGraphicsContext() override = default;

        void Init() override;
        void SwapBuffers() override;

        std::shared_ptr<VulkanPhysicalDevice> GetPhysicalDevice() const { return m_PhysicalDevice; }
        std::shared_ptr<VulkanSurface> GetSurface() const { return m_Surface; }
        std::shared_ptr<VulkanDevice> GetDevice() const { return m_Device; }
    private:
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<VulkanInstance> m_VulkanInstance;
        std::shared_ptr<VulkanSurface> m_Surface;
        std::shared_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
        std::shared_ptr<VulkanDevice> m_Device;
        std::shared_ptr<VulkanSwapChain> m_SwapChain;
    };
}
