#pragma once
#include "VulkanBuffer.h"
#include "renderer/buffers/IIndexBuffer.h"

namespace Lada {
    class VulkanIndexBuffer final : public VulkanBuffer, public IIndexBuffer {
    public:
        VulkanIndexBuffer(VulkanGraphicsContext* graphicsContext, uint64_t instanceSize, uint32_t instanceCount, bool withStaging);

        void Bind(CommandBuffer* commandBuffer) override;

        void Map(uint64_t size, uint64_t offset) override;

        void Unmap() override;

        void WriteToBuffer(const void *data, uint64_t size, uint64_t offset) override;
    };
}
