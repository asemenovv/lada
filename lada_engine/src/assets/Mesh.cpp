#include "Mesh.h"

#include "platform/vulkan/buffers/VulkanIndexBuffer.h"
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
        m_VertexBuffer = std::make_unique<VulkanVertexBuffer>(vulkanContext, vertexSize, m_Vertices.size());
        m_VertexBuffer->Map();
        m_VertexBuffer->WriteToBuffer(m_Vertices.data());

        m_IndexBuffer = std::make_unique<VulkanIndexBuffer>(vulkanContext, indexSize, m_Indices.size());
        m_IndexBuffer->Map();
        m_IndexBuffer->WriteToBuffer(m_Indices.data());
    }
}
