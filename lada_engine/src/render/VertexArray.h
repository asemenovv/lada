#pragma once

#include "VertexBuffer.h"

namespace Lada::Render {
    class VertexBufferLayout;

    class VertexArray {
        unsigned int m_RendererID;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
    };
}
