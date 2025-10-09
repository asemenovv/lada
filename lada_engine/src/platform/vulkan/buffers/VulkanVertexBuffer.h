#pragma once
#include "VulkanBuffer.h"
#include "renderer/buffers/IVertexBuffer.h"

namespace Lada {
    class VulkanVertexBuffer final : public VulkanBuffer, public IVertexBuffer {
    public:
        VulkanVertexBuffer(VulkanGraphicsContext* graphicsContext, uint64_t instanceSize, uint32_t instanceCount);

        void Bind(CommandBuffer* commandBuffer) override;

        void Map(uint64_t size, uint64_t offset) override;

        void Unmap() override;

        void WriteToBuffer(const void *data, uint64_t size, uint64_t offset) const override;
    };
}
