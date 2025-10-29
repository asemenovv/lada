#pragma once

#include <memory>

#include "VulkanPipelineLayout.h"
#include "VulkanRenderPass.h"
#include "VulkanShader.h"
#include "renderer/Pipeline.h"

namespace Lada {
    class VulkanPipeline : public Pipeline {
    public:
        // TODO: Move shader to PipelineCreateInfo
        VulkanPipeline(VulkanGraphicsContext* graphicsContext, const PipelineCreateInfo &createInfo);

        ~VulkanPipeline();

        RenderPass* GetRenderPass() override { return m_RenderPass.get(); }

        void Bind(CommandBuffer* commandBuffer) override;
    private:
        void createGraphicsPipeline(/*const PipelineConfigInfo &configInfo*/);

        VkPipeline m_Pipeline;
        VulkanGraphicsContext* m_GraphicsContext;
        std::unique_ptr<VulkanPipelineLayout> m_Layout;
        std::unique_ptr<VulkanRenderPass> m_RenderPass;
        PipelineCreateInfo m_CreateInfo;
    };
}
