#pragma once

namespace Lada::Render {
    class DeprecatedVertexBuffer {
        unsigned int m_RendererID;
    public:
        DeprecatedVertexBuffer(const void* data, unsigned int size);
        ~DeprecatedVertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}
