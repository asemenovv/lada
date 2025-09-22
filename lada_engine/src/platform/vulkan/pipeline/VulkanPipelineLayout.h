#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

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
