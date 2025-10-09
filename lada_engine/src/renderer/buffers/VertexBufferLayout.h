#pragma once

#include "VertexBufferElement.h"

namespace Lada {
    class VertexBufferLayout {
    public:
        VertexBufferLayout() = default;
        ~VertexBufferLayout() = default;

        void AddElement(const ShaderDataType &type, const std::string& name, const bool normalized = false);

        uint32_t GetStride() const;

        uint32_t GetElementCount() const;

        [[nodiscard]] std::vector<VertexBufferElement>::iterator begin();

        [[nodiscard]] std::vector<VertexBufferElement>::iterator end();

        [[nodiscard]] std::vector<VertexBufferElement>::const_iterator begin() const;

        [[nodiscard]] std::vector<VertexBufferElement>::const_iterator end() const;

    private:
        std::vector<VertexBufferElement> m_Elements;
        uint32_t m_Stride = 0;

        void updateOffsetsAndStride();
    };
}
