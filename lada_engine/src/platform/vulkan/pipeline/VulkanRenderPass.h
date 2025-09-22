#pragma once

#include <vulkan/vulkan.h>

#include "renderer/RenderPass.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanRenderPass : public RenderPass {
    public:
        explicit VulkanRenderPass(VulkanGraphicsContext *graphicsContext);

        ~VulkanRenderPass();

        VkRenderPass NativeRenderPass() const { return m_RenderPass; }

        void Begin(CommandBuffer* commandBuffer, uint32_t currentImageIndex, const glm::vec4 &clearColor) const override;

        void End(CommandBuffer *commandBuffer) const override;

        void SetViewportAndScissor(CommandBuffer *commandBuffer, const Render::Viewport &viewport,
                                   const Render::Scissor &scissor) const override;
    private:
        VulkanGraphicsContext *m_GraphicsContext;
        VkRenderPass m_RenderPass;
    };
}
