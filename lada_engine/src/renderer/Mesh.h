#pragma once
#include <memory>

#include "buffers/IndexBuffer.h"
#include "buffers/VertexBuffer.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBufferLayout.h"
#include "material/Material.h"

namespace Lada::Render {
    class Mesh {
    public:
        Mesh(std::shared_ptr<VertexBuffer> vertexBuffer, const std::shared_ptr<VertexArray> &vertexArray,
             const std::shared_ptr<IndexBuffer> &indexBuffer, const std::shared_ptr<Material> &material);

        void Draw() const;

        void SetMaterial(const std::shared_ptr<Material> &material) {m_Material = material; }

    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Material> m_Material;
    };

    class MeshBuilder {
    public:
        MeshBuilder(const void* data, unsigned int size);

        MeshBuilder PushFloatToLayout(const unsigned int count);

        template<typename T>
        MeshBuilder& PushToLayout(const unsigned int count) {}

        template<typename T>
        MeshBuilder& PushToLayoutIf(bool condition, const unsigned int count) {}

        template<>
        MeshBuilder& PushToLayoutIf<float>(bool condition, unsigned int count);

        MeshBuilder& FinalizeBuffer();

        MeshBuilder& Indices(const unsigned int* data, unsigned int count);

        MeshBuilder& WithMaterial(std::shared_ptr<Material> material);

        std::shared_ptr<Mesh> Build();
    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Material> m_Material;
        std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
    };
}
