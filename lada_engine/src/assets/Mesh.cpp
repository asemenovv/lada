#include "Mesh.h"

namespace Lada {
    Mesh::Mesh(const AssetID &id): Asset(id, AssetType::Mesh), m_Vertices({}), m_Indices({}) {
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
}
