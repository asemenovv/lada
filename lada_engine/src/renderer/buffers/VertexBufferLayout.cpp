#include "VertexBufferLayout.h"

namespace Lada {
    void VertexBufferLayout::AddElement(const ShaderDataType &type, const std::string &name, const bool normalized) {
        m_Elements.push_back({type, name, normalized});
        updateOffsetsAndStride();
    }

    uint32_t VertexBufferLayout::GetStride() const {
        return m_Stride;
    }

    uint32_t VertexBufferLayout::GetElementCount() const {
        return static_cast<uint32_t>(m_Elements.size());
    }

    std::vector<VertexBufferElement>::iterator VertexBufferLayout::begin() {
        return m_Elements.begin();
    }

    std::vector<VertexBufferElement>::iterator VertexBufferLayout::end() {
        return m_Elements.end();
    }

    std::vector<VertexBufferElement>::const_iterator VertexBufferLayout::begin() const {
        return m_Elements.begin();
    }

    std::vector<VertexBufferElement>::const_iterator VertexBufferLayout::end() const {
        return m_Elements.end();
    }

    void VertexBufferLayout::updateOffsetsAndStride() {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements) {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
}
