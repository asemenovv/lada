#include  "ldpch.h"
#include  "DeprecatedMesh.h"

#include "material/Material.h"
#include "../app/GlCall.h"

namespace Lada::Render {
    DeprecatedMesh::DeprecatedMesh(const std::shared_ptr<DeprecatedVertexBuffer> vertexBuffer,
               const std::shared_ptr<VertexArray> &vertexArray,
               const std::shared_ptr<IndexBuffer> &indexBuffer)
        : m_VertexBuffer(vertexBuffer), m_VertexArray(vertexArray),
          m_IndexBuffer(indexBuffer) {
    }

    void DeprecatedMesh::Draw() const {
        m_VertexArray->Bind();
        m_IndexBuffer->Bind();

        GL_CALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    MeshBuilder::MeshBuilder(const void *data, unsigned int size) {
        m_VertexArray = std::make_shared<VertexArray>();
        m_VertexBuffer = std::make_shared<DeprecatedVertexBuffer>(data, size);
        m_VertexBufferLayout = std::make_unique<DepricatedVertexBufferLayout>();
    }

    template<>
    MeshBuilder &MeshBuilder::PushToLayout<float>(const unsigned int count) {
        m_VertexBufferLayout->Push<float>(count);
        return *this;
    }

    template<>
    MeshBuilder &MeshBuilder::PushToLayoutIf<float>(const bool condition, const unsigned int count) {
        if (condition) {
            PushToLayout<float>(count);
        }
        return *this;
    }

    MeshBuilder& MeshBuilder::FinalizeBuffer() {
        m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
        return *this;
    }

    MeshBuilder & MeshBuilder::Indices(const unsigned int *data, unsigned int count) {
        m_IndexBuffer = std::make_shared<IndexBuffer>(data, count);
        return *this;
    }

    std::shared_ptr<DeprecatedMesh> MeshBuilder::Build() {
        auto mesh = std::make_shared<DeprecatedMesh>(m_VertexBuffer, m_VertexArray, m_IndexBuffer);
        return mesh;
    }
}
