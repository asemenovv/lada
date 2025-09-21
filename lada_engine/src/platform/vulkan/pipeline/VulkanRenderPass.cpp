#include "VulkanRenderPass.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanSwapChain.h"

namespace Lada {
    VulkanRenderPass::VulkanRenderPass(VulkanGraphicsContext *graphicsContext):
        m_GraphicsContext(graphicsContext) {
        VulkanSwapChain& swapChain = graphicsContext->GetSwapChain();

        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = swapChain.GetImage(0).GetFormat();
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

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        LD_VK_ASSERT_SUCCESS(vkCreateRenderPass(graphicsContext->GetDevice().NativeDevice(),
            &renderPassInfo, nullptr, &m_RenderPass), "Failed to create render pass!");
    }

    VulkanRenderPass::~VulkanRenderPass() {
        vkDestroyRenderPass(m_GraphicsContext->GetDevice().NativeDevice(), m_RenderPass, nullptr);
    }
} // Lada