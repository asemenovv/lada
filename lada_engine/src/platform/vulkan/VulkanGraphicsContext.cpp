#include "VulkanGraphicsContext.h"

#include "commands/VulkanCommandPool.h"
#include "VulkanSwapChain.h"
#include "app/Logger.h"
#include "pipeline/VulkanPipeline.h"
#include "VulkanFramebuffer.h"
#include "assets/Mesh.h"
#include "commands/VulkanCommandBuffer.h"

namespace Lada {
    VulkanGraphicsContext::VulkanGraphicsContext(Window& window): m_Window(window) {
    }

    VulkanGraphicsContext::~VulkanGraphicsContext() {
    }

    void VulkanGraphicsContext::Init() {
        bool enableValidationLayers = true;
        const auto [width, height] = m_Window.GetPixelsSize();
        auto extent = VkExtent2D(width, height);
        m_VulkanInstance = std::make_unique<VulkanInstance>(enableValidationLayers);
        m_Surface = std::make_unique<VulkanSurface>(*m_VulkanInstance, m_Window);
        m_PhysicalDevice = std::make_unique<VulkanPhysicalDevice>(*m_VulkanInstance, *m_Surface);
        m_Device = std::make_unique<VulkanDevice>(*m_VulkanInstance, *m_PhysicalDevice, enableValidationLayers);
        m_SwapChain = std::make_unique<VulkanSwapChain>(this, extent);
        PipelineCreateInfo createInfo = {
            .Layout = Mesh::Vertex::Layout()
        };
        m_Pipeline = std::make_unique<VulkanPipeline>(this, createInfo,
            "/Users/alexeysemenov/CLionProjects/lada/assets/shaders/simple_shader.vert.spv",
            "/Users/alexeysemenov/CLionProjects/lada/assets/shaders/simple_shader.frag.spv");
        crateFrameBuffers();
        m_CommandPool = std::make_unique<VulkanCommandPool>(this);
    }

    void VulkanGraphicsContext::crateFrameBuffers() {
        swapChainFramebuffers.clear();
        swapChainFramebuffers.resize(m_SwapChain->GetImageCount());
        for (size_t i = 0; i < m_SwapChain->GetImageCount(); i++) {
            VulkanImage& image = m_SwapChain->GetImage(i);
            swapChainFramebuffers[i] = std::make_unique<VulkanFramebuffer>(this, image);
        }
    }

    void VulkanGraphicsContext::SwapBuffers() {
    }

    void VulkanGraphicsContext::SetDebugName(const uint64_t handle, const VkObjectType type, const char *name) {
        m_Device->SetDebugName(handle, type, name);
    }

    std::unique_ptr<CommandBuffer> VulkanGraphicsContext::CreateCommandBuffer() {
        return std::make_unique<VulkanCommandBuffer>(this, m_CommandPool.get());
    }

    void VulkanGraphicsContext::EndSingleTimeCommands(CommandBuffer *commandBuffer) {
        const auto vulkanCommandBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer);
        LD_VK_ASSERT_SUCCESS(vkEndCommandBuffer(vulkanCommandBuffer->NativeCommandBuffer()), "Failed to record command buffer!");
    }

    VulkanFramebuffer& VulkanGraphicsContext::GetFramebuffer(const uint32_t index) const {
        return *swapChainFramebuffers[index];
    }

    void VulkanGraphicsContext::RecreateSwapChain() {
        WaitIdle();
        const auto [width, height] = m_Window.GetPixelsSize();
        auto extent = VkExtent2D(width, height);
        m_SwapChain = std::make_unique<VulkanSwapChain>(this, extent, m_SwapChain.get());
        crateFrameBuffers();
    }

    void VulkanGraphicsContext::WaitIdle() {
        vkDeviceWaitIdle(GetDevice().NativeDevice());
    }
}
