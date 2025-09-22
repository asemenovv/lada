#pragma once

#include "Camera.h"
#include "glm/glm.hpp"

namespace Lada {
    class CommandBuffer;

    class RenderPass {
    public:
        virtual void Begin(CommandBuffer* commandBuffer, uint32_t currentImageIndex, const glm::vec4& clearColor) const = 0;

        virtual void End(CommandBuffer* commandBuffer) const = 0;

        virtual void SetViewportAndScissor(CommandBuffer* commandBuffer, const Render::Viewport& viewport, const Render::Scissor& scissor) const = 0;
    };
}
