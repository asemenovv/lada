#include "VulkanFramebuffer.h"

#include "VulkanSwapChain.h"
#include "app/Logger.h"
#include "buffers/VulkanImage.h"
#include "pipeline/VulkanPipeline.h"

namespace Lada {
    VulkanFramebuffer::VulkanFramebuffer(VulkanGraphicsContext *graphicsContext, VulkanImage& image)
        : m_GraphicsContext(graphicsContext) {
        VkDevice device = graphicsContext->GetDevice().NativeDevice();
        const VkRenderPass &renderPass = graphicsContext->GetPipeline().GetRenderPass()->NativeRenderPass();
        const VkImageView attachments[] = { image.GetView() };
        const auto [width, height] = graphicsContext->GetSwapChain().GetSwapChainExtent();

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = width;
        framebufferInfo.height = height;
        framebufferInfo.layers = 1;
        LD_VK_ASSERT_SUCCESS(vkCreateFramebuffer(device, &framebufferInfo, nullptr,&m_Framebuffer),
            "Failed to create framebuffer!");
    }

    VulkanFramebuffer::~VulkanFramebuffer() {
        vkDestroyFramebuffer(m_GraphicsContext->GetDevice().NativeDevice(), m_Framebuffer, nullptr);
    }
}
