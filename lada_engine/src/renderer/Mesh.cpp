#include  "ldpch.h"
#include  "Mesh.h"

#include "material/Material.h"
#include "render/Renderer.h"

namespace Lada::Render {
    Mesh::Mesh(const std::shared_ptr<VertexBuffer> vertexBuffer,
               const std::shared_ptr<VertexArray> &vertexArray,
               const std::shared_ptr<IndexBuffer> &indexBuffer,
               const std::shared_ptr<Material> &material)
        : m_VertexBuffer(vertexBuffer), m_VertexArray(vertexArray),
          m_IndexBuffer(indexBuffer), m_Material(material) {
    }

    void Mesh::Draw() const {
        m_Material->Bind();
        m_VertexArray->Bind();
        m_IndexBuffer->Bind();

        GL_CALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    MeshBuilder::MeshBuilder(const void *data, unsigned int size) {
        m_VertexArray = std::make_shared<VertexArray>();
        m_VertexBuffer = std::make_shared<VertexBuffer>(data, size);
        m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
    }

    template<>
    MeshBuilder &MeshBuilder::PushToLayout<float>(const unsigned int count) {
        m_VertexBufferLayout->Push<float>(count);
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

    MeshBuilder & MeshBuilder::WithMaterial(std::shared_ptr<Render::Material> material) {
        m_Material = material;
        return *this;
    }

    std::shared_ptr<Mesh> MeshBuilder::Build() {
        auto mesh = std::make_shared<Mesh>(m_VertexBuffer, m_VertexArray, m_IndexBuffer, m_Material);
        return mesh;
    }
}
