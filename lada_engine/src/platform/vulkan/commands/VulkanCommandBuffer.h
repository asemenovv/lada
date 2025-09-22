#pragma once

#include "VulkanCommandPool.h"
#include "platform/vulkan/pipeline/VulkanRenderPass.h"
#include "renderer/CommandBuffer.h"

namespace Lada {
    class VulkanCommandBuffer : public CommandBuffer {
    public:
        explicit VulkanCommandBuffer(VulkanGraphicsContext *graphicsContext, const VulkanCommandPool *pool);

        VkCommandBuffer GetNativeCommandBuffer() const { return m_CommandBuffer; }
    private:
        VkCommandBuffer m_CommandBuffer;
        VulkanGraphicsContext *m_GraphicsContext;
    };
}
