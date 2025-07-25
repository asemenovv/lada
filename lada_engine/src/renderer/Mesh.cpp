#include  "ldpch.h"
#include  "Mesh.h"

#include "material/Material.h"
#include "render/Renderer.h"

namespace Lada::Render {
    Mesh::Mesh(const std::shared_ptr<VertexBuffer> &vertexBuffer,
               const std::shared_ptr<IndexBuffer> &indexBuffer,
               const std::shared_ptr<Material> &material)
    : m_IndexBuffer(indexBuffer), m_VertexBuffer(vertexBuffer), m_Material(material) {
    }

    void Mesh::Draw() const {
        m_Material->Bind();
        m_VertexBuffer->Bind();
        m_IndexBuffer->Bind();

        GL_CALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}
