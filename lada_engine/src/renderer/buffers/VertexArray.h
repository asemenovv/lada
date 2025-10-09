#pragma once

#include "DeprecatedVertexBuffer.h"

namespace Lada::Render {
    class DepricatedVertexBufferLayout;

    class VertexArray {
        unsigned int m_RendererID;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const DeprecatedVertexBuffer& vb, const DepricatedVertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
    };
}
