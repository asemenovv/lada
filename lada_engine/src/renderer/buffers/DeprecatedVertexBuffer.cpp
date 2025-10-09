#include "ldpch.h"
#include "DeprecatedVertexBuffer.h"
#include "app/GlCall.h"
#include "renderer/Renderer.h"

#include "VertexBufferElement.h"

namespace Lada::Render {
    DeprecatedVertexBuffer::DeprecatedVertexBuffer(const void *data, unsigned int size) {
        GL_CALL(glGenBuffers(1, &m_RendererID));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    DeprecatedVertexBuffer::~DeprecatedVertexBuffer() {
        GL_CALL(glDeleteBuffers(1, &m_RendererID));
    }

    void DeprecatedVertexBuffer::Bind() const {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void DeprecatedVertexBuffer::Unbind() const {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}
