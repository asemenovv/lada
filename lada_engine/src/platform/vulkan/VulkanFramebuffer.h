#pragma once

#include "buffers/VulkanImage.h"

namespace Lada {
    class VulkanFramebuffer {
    public:
        VulkanFramebuffer(VulkanGraphicsContext* graphicsContext, VulkanImage &image);
        ~VulkanFramebuffer();

        VkFramebuffer GetNativeFramebuffer() const { return m_Framebuffer; }
    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkFramebuffer m_Framebuffer;
    };
}
