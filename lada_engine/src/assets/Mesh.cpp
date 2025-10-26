#include "Mesh.h"

#include "platform/vulkan/buffers/VulkanIndexBuffer.h"
#include "platform/vulkan/buffers/VulkanStagingBuffer.h"
#include "platform/vulkan/buffers/VulkanVertexBuffer.h"

namespace Lada {
    Mesh::Mesh(const AssetID &id, GraphicsContext* graphicsContext)
        : Asset(id, AssetType::Mesh), m_Vertices({}), m_Indices({}), m_GraphicsContext(graphicsContext) {
    }

    size_t Mesh::VerticesCount() const {
        return m_Vertices.size();
    }

    void Mesh::AddVertex(const Vertex &vertex) {
        m_Vertices.push_back(vertex);
    }

    void Mesh::AddIndex(const uint32_t vertexIndex) {
        m_Indices.push_back(vertexIndex);
    }

    void Mesh::LoadBuffers() {
        constexpr uint32_t vertexSize = sizeof(m_Vertices[0]);
        constexpr uint32_t indexSize = sizeof(m_Indices[0]);
        auto vulkanContext = reinterpret_cast<VulkanGraphicsContext*>(m_GraphicsContext);

        auto stagingVertexBuffer = VulkanStagingBuffer(vulkanContext, vertexSize, m_Vertices.size());
        stagingVertexBuffer.Map();
        stagingVertexBuffer.WriteToBuffer(m_Vertices.data());
        m_VertexBuffer = std::make_unique<VulkanVertexBuffer>(vulkanContext, vertexSize, m_Vertices.size(), true);
        stagingVertexBuffer.CopyToBuffer(dynamic_cast<VulkanBuffer*>(m_VertexBuffer.get()));

        auto stagingIndexBuffer = VulkanStagingBuffer(vulkanContext, indexSize, m_Indices.size());
        stagingIndexBuffer.Map();
        stagingIndexBuffer.WriteToBuffer(m_Indices.data());
        m_IndexBuffer = std::make_unique<VulkanIndexBuffer>(vulkanContext, indexSize, m_Indices.size(), true);
        stagingIndexBuffer.CopyToBuffer(dynamic_cast<VulkanBuffer*>(m_IndexBuffer.get()));
    }
}
