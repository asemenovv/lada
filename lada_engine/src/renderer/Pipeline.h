#pragma once

#include "CommandBuffer.h"
#include "RenderPass.h"
#include "buffers/VertexBufferLayout.h"
#include "platform/vulkan/pipeline/VulkanShaderCollection.h"

namespace Lada {
    struct PipelineCreateInfo {
        VertexBufferLayout Layout = VertexBufferLayout();
        ShaderCollection* ShaderCollection;
    };

    class Pipeline {
    public:
        virtual RenderPass* GetRenderPass() = 0;
        virtual void Bind(CommandBuffer* commandBuffer) = 0;
    };
}
