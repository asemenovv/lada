#pragma once

#include "VulkanFramebuffer.h"
#include "VulkanSwapChain.h"
#include "commands/VulkanCommandPool.h"
#include "device/VulkanDevice.h"
#include "device/VulkanInstance.h"
#include "device/VulkanPhysicalDevice.h"
#include "device/VulkanSurface.h"
#include "pipeline/VulkanPipeline.h"
#include "renderer/GraphicsContext.h"

namespace Lada {
    class VulkanCommandBuffer;
}

struct GLFWwindow;

namespace Lada {
    class VulkanGraphicsContext final : public GraphicsContext,
                                        public std::enable_shared_from_this<VulkanGraphicsContext> {
    public:
        explicit VulkanGraphicsContext(Window& window);
        ~VulkanGraphicsContext() override;

        void Init() override;
        void SwapBuffers() override;

        void SetDebugName(const uint64_t handle, const VkObjectType type, const char *name);

        std::unique_ptr<CommandBuffer> CreateCommandBuffer() override;

        void EndSingleTimeCommands(CommandBuffer *commandBuffer) override;

        VulkanPhysicalDevice& GetPhysicalDevice() const { return *m_PhysicalDevice; }
        VulkanSurface& GetSurface() const { return *m_Surface; }
        VulkanDevice& GetDevice() const { return *m_Device; }
        VulkanSwapChain* GetSwapChain() const override { return m_SwapChain.get(); }
        Pipeline* GetPipeline() const override { return m_Pipeline.get(); }

        VulkanFramebuffer& GetFramebuffer(uint32_t index) const;
    private:
        std::unique_ptr<VulkanInstance> m_VulkanInstance;
        std::unique_ptr<VulkanSurface> m_Surface;
        std::unique_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
        std::unique_ptr<VulkanDevice> m_Device;
        std::unique_ptr<VulkanSwapChain> m_SwapChain;
        std::vector<std::unique_ptr<VulkanFramebuffer>> swapChainFramebuffers;
        std::unique_ptr<VulkanPipeline> m_Pipeline;
        std::unique_ptr<VulkanCommandPool> m_CommandPool;
        Window& m_Window;

        void crateFrameBuffers();
    };
}
