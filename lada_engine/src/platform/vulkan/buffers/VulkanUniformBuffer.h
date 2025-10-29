#pragma once
#include "VulkanBuffer.h"
#include "renderer/buffers/IUniformBuffer.h"
#include "renderer/buffers/IVertexBuffer.h"

namespace Lada {
    class GraphicsContext;

    class VulkanUniformBuffer final : public VulkanBuffer, public IUniformBuffer {
    public:
        VulkanUniformBuffer(GraphicsContext* graphicsContext, uint64_t instanceSize);

        void Map(uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) override;

        void Unmap() override;

        void WriteToBuffer(const void *data, uint64_t size = LD_BUFFER_WHOLE_SIZE, uint64_t offset = 0) const override;
    };
}
