#pragma once

#include <vulkan/vulkan.h>

#include "VulkanShaderCollection.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanPipelineLayout {
    public:
        explicit VulkanPipelineLayout(VulkanGraphicsContext* graphicsContext, ShaderCollection* shaderCollection);
        ~VulkanPipelineLayout();

        VkPipelineLayout NativeLayout() const { return m_PipelineLayout; }
    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkPipelineLayout m_PipelineLayout;
    };
}
