#pragma once

#include "VulkanCommandPool.h"
#include "platform/vulkan/pipeline/VulkanRenderPass.h"
#include "renderer/CommandBuffer.h"

namespace Lada {
    class VulkanCommandBuffer : public CommandBuffer {
    public:
        explicit VulkanCommandBuffer(VulkanGraphicsContext *graphicsContext, const VulkanCommandPool *pool);

        VkCommandBuffer NativeCommandBuffer() const { return m_CommandBuffer; }

        void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;

        void Reset() override;

        void Begin() override;

        void End() override;
    private:
        VkCommandBuffer m_CommandBuffer;
        VulkanGraphicsContext *m_GraphicsContext;
    };
}
