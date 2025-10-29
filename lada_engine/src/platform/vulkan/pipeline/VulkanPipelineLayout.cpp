#include "VulkanPipelineLayout.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    VulkanPipelineLayout::VulkanPipelineLayout(VulkanGraphicsContext *graphicsContext, ShaderCollection* shaderCollection)
        : m_GraphicsContext(graphicsContext) {
        const VkDescriptorSetLayout descriptorSetLayout = shaderCollection->CreateDescriptorSetLayout();
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        LD_VK_ASSERT_SUCCESS(vkCreatePipelineLayout(graphicsContext->GetDevice().NativeDevice(), &pipelineLayoutInfo,
            nullptr, &m_PipelineLayout), "Failed to create pipeline layout!")
    }

    VulkanPipelineLayout::~VulkanPipelineLayout() {
        vkDestroyPipelineLayout(m_GraphicsContext->GetDevice().NativeDevice(), m_PipelineLayout, nullptr);
    }
}
