#pragma once
#include <memory>

#include "buffers/IndexBuffer.h"
#include "buffers/DeprecatedVertexBuffer.h"
#include "buffers/VertexArray.h"
#include "buffers/DepricatedVertexBufferLayout.h"
#include "material/Material.h"

namespace Lada::Render {
    class DeprecatedMesh {
    public:
        DeprecatedMesh(std::shared_ptr<DeprecatedVertexBuffer> vertexBuffer, const std::shared_ptr<VertexArray> &vertexArray,
             const std::shared_ptr<IndexBuffer> &indexBuffer);

        void Draw() const;

    private:
        std::shared_ptr<DeprecatedVertexBuffer> m_VertexBuffer;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };

    class MeshBuilder {
    public:
        MeshBuilder(const void *data, unsigned int size);

        MeshBuilder PushFloatToLayout(const unsigned int count);

        template<typename T>
        MeshBuilder &PushToLayout(const unsigned int count);

        template<typename T>
        MeshBuilder &PushToLayoutIf(bool condition, const unsigned int count);

        template<>
        MeshBuilder &PushToLayoutIf<float>(bool condition, unsigned int count);

        MeshBuilder &FinalizeBuffer();

        MeshBuilder &Indices(const unsigned int *data, unsigned int count);

        std::shared_ptr<DeprecatedMesh> Build();

    private:
        std::shared_ptr<DeprecatedVertexBuffer> m_VertexBuffer;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Material> m_Material;
        std::unique_ptr<DepricatedVertexBufferLayout> m_VertexBufferLayout;
    };
}
