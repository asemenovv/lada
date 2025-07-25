#pragma once
#include <memory>

#include "buffers/IndexBuffer.h"
#include "buffers/VertexBuffer.h"
#include "material/Material.h"

namespace Lada::Render {
    class Mesh {
    public:
        Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer,
            const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<Material>& material);

        void Draw() const;
    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Material> m_Material;
    };
}
