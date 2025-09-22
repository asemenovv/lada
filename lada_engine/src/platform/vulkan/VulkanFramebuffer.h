#pragma once

#include "VulkanGraphicsContext.h"
#include "buffers/VulkanImage.h"

namespace Lada {
    class VulkanFramebuffer {
    public:
        VulkanFramebuffer(VulkanGraphicsContext* graphicsContext, VulkanImage &image);
        ~VulkanFramebuffer();
    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkFramebuffer m_Framebuffer;
    };
}
