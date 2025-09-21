#pragma once

#include <memory>

#include "VulkanPipelineLayout.h"
#include "VulkanRenderPass.h"
#include "VulkanShader.h"

namespace Lada {
    class VulkanPipeline {
    public:
        VulkanPipeline(VulkanGraphicsContext* graphicsContext, const std::string &vertPath,
                       const std::string &fragPath);
        ~VulkanPipeline();
    private:
        void createGraphicsPipeline(/*const PipelineConfigInfo &configInfo*/);

        VkPipeline m_Pipeline;
        VulkanGraphicsContext* m_GraphicsContext;
        std::unique_ptr<VulkanShader> m_VertShader;
        std::unique_ptr<VulkanShader>  m_FragShader;
        std::unique_ptr<VulkanPipelineLayout> m_Layout;
        std::unique_ptr<VulkanRenderPass> m_RenderPass;
    };
}
