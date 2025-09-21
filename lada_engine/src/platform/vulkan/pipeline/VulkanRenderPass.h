#pragma once

#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    class VulkanRenderPass {
    public:
        explicit VulkanRenderPass(VulkanGraphicsContext *graphicsContext);

        ~VulkanRenderPass();

        VkRenderPass NativeRenderPass() const { return m_RenderPass; }

    private:
        VulkanGraphicsContext *m_GraphicsContext;
        VkRenderPass m_RenderPass;
    };
}
