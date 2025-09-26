#include "VulkanRenderPass.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"
#include "platform/vulkan/VulkanSwapChain.h"
#include "platform/vulkan/commands/VulkanCommandBuffer.h"

namespace Lada {
    VulkanRenderPass::VulkanRenderPass(VulkanGraphicsContext *graphicsContext) : m_GraphicsContext(graphicsContext) {
        VulkanSwapChain* swapChain = graphicsContext->GetSwapChain();

        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = swapChain->GetImage(0).GetFormat();
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        LD_VK_ASSERT_SUCCESS(vkCreateRenderPass(graphicsContext->GetDevice().NativeDevice(),
                                 &renderPassInfo, nullptr, &m_RenderPass), "Failed to create render pass!");
    }

    VulkanRenderPass::~VulkanRenderPass() {
        vkDestroyRenderPass(m_GraphicsContext->GetDevice().NativeDevice(), m_RenderPass, nullptr);
    }

    void VulkanRenderPass::Begin(CommandBuffer *commandBuffer, uint32_t currentImageIndex,
                                 const glm::vec4 &clearColor) const {
        const auto vulkanCommandBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer);
        const VkExtent2D swapChainExtent = m_GraphicsContext->GetSwapChain()->GetSwapChainExtent();
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_RenderPass;
        renderPassInfo.framebuffer = m_GraphicsContext->GetFramebuffer(currentImageIndex).GetNativeFramebuffer();

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChainExtent;

        const VkClearValue vkClearColor = {{{clearColor.r, clearColor.g, clearColor.b, clearColor.a}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &vkClearColor;

        vkCmdBeginRenderPass(vulkanCommandBuffer->NativeCommandBuffer(), &renderPassInfo,
                             VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanRenderPass::End(CommandBuffer *commandBuffer) const {
        const auto vulkanCommandBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer);
        vkCmdEndRenderPass(vulkanCommandBuffer->NativeCommandBuffer());
    }

    void VulkanRenderPass::SetViewportAndScissor(CommandBuffer *commandBuffer, const Render::Viewport &viewport,
                                                 const Render::Scissor &scissor) const {
        const auto vulkanCommandBuffer = static_cast<VulkanCommandBuffer *>(commandBuffer);
        VkExtent2D swapChainExtent = m_GraphicsContext->GetSwapChain()->GetSwapChainExtent();
        VkViewport vkViewport{};
        vkViewport.x = viewport.X;
        vkViewport.y = viewport.Y;
        vkViewport.width = swapChainExtent.width * viewport.Width;
        vkViewport.height = swapChainExtent.height * viewport.Height;
        vkViewport.minDepth = viewport.MinDepth;
        vkViewport.maxDepth = viewport.MaxDepth;
        vkCmdSetViewport(vulkanCommandBuffer->NativeCommandBuffer(), 0, 1, &vkViewport);

        VkRect2D vkScissor{};
        vkScissor.offset = {
            static_cast<int32_t>(scissor.OffsetX * swapChainExtent.width),
            static_cast<int32_t>(scissor.OffsetX * swapChainExtent.height)
        };
        vkScissor.extent = {
            static_cast<uint32_t>(scissor.Width * swapChainExtent.width),
            static_cast<uint32_t>(scissor.Height * swapChainExtent.height)
        };
        vkCmdSetScissor(vulkanCommandBuffer->NativeCommandBuffer(), 0, 1, &vkScissor);
    }
} // Lada
