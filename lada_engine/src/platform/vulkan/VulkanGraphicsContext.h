#pragma once

#include "device/VulkanDevice.h"
#include "device/VulkanInstance.h"
#include "device/VulkanPhysicalDevice.h"
#include "device/VulkanSurface.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class VulkanSwapChain;

    class VulkanGraphicsContext final : public GraphicsContext,
                                        public std::enable_shared_from_this<VulkanGraphicsContext> {
    public:
        explicit VulkanGraphicsContext(Window& window);
        ~VulkanGraphicsContext() override;

        void Init() override;
        void SwapBuffers() override;

        void SetDebugName(const uint64_t handle, const VkObjectType type, const char *name);

        VulkanPhysicalDevice& GetPhysicalDevice() const { return *m_PhysicalDevice; }
        VulkanSurface& GetSurface() const { return *m_Surface; }
        VulkanDevice& GetDevice() const { return *m_Device; }
    private:
        std::unique_ptr<VulkanInstance> m_VulkanInstance;
        std::unique_ptr<VulkanSurface> m_Surface;
        std::unique_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
        std::unique_ptr<VulkanDevice> m_Device;
        std::unique_ptr<VulkanSwapChain> m_SwapChain;
        Window& m_Window;
    };
}
