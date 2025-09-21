#pragma once

#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    class VulkanPipelineLayout {
    public:
        explicit VulkanPipelineLayout(VulkanGraphicsContext* graphicsContext);
        ~VulkanPipelineLayout();

        VkPipelineLayout NativeLayout() const { return m_PipelineLayout; }
    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkPipelineLayout m_PipelineLayout;
    };
}
