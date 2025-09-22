#pragma once

#include "glm/glm.hpp"

namespace Lada {
    class CommandBuffer;

    class RenderPass {
    public:
        virtual void Begin(CommandBuffer* commandBuffer, uint32_t currentImageIndex, const glm::vec4& clearColor) const = 0;
    };
}
