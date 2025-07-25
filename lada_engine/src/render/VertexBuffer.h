#pragma once

namespace Lada::Render {
    class VertexBuffer {
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}
