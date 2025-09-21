#pragma once

#include <memory>

#include "VulkanShader.h"

namespace Lada {
    class VulkanPipeline {
    public:
        VulkanPipeline(VulkanGraphicsContext* graphicsContext, const std::string &vertPath,
                       const std::string &fragPath);
        ~VulkanPipeline();
    private:
        void createGraphicsPipeline(/*const PipelineConfigInfo &configInfo*/);

        VulkanGraphicsContext* m_GraphicsContext;
        std::unique_ptr<VulkanShader> m_VertShader;
        std::unique_ptr<VulkanShader>  m_FragShader;
    };
}
