#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>

#include "Asset.h"
#include "renderer/buffers/IIndexBuffer.h"
#include "renderer/buffers/IVertexBuffer.h"
#include "renderer/buffers/VertexBufferLayout.h"

namespace Lada {
    class GraphicsContext;

    class Mesh final : public Asset {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec3 normal;
            glm::vec2 uv;

            bool operator==(const Vertex &other) const {
                return position == other.position && normal == other.normal && color == other.color && uv == other.uv;
            }

            static VertexBufferLayout Layout() {
                VertexBufferLayout layout;
                layout.AddElement(ShaderDataType::Float3, "a_Position");
                layout.AddElement(ShaderDataType::Float3, "a_Color");
                layout.AddElement(ShaderDataType::Float3, "a_Normal");
                layout.AddElement(ShaderDataType::Float2, "a_UV");
                return layout;
            }
        };

        struct VertexHash {
            std::size_t operator()(const Vertex& v) const noexcept {
                std::size_t seed = 0;
                auto hc = [](std::size_t& seed, std::size_t h) {
                    seed ^= h + 0x9e3779b97f4a7c15ULL + (seed<<6) + (seed>>2);
                };
                hc(seed, std::hash<glm::vec3>{}(v.position));
                hc(seed, std::hash<glm::vec3>{}(v.normal));
                hc(seed, std::hash<glm::vec3>{}(v.color));
                hc(seed, std::hash<glm::vec2>{}(v.uv));
                return seed;
            }
        };

        explicit Mesh(const AssetID &id, GraphicsContext* graphicsContext);

        ~Mesh() override = default;

        [[nodiscard]] size_t VerticesCount() const;

        void AddVertex(const Vertex &vertex);

        void AddIndex(uint32_t vertexIndex);

        void LoadBuffers();

        [[nodiscard]] IVertexBuffer* GetVertexBuffer() const { return m_VertexBuffer.get(); }

        [[nodiscard]] IIndexBuffer* GetIndexBuffer() const { return m_IndexBuffer.get(); }

        uint32_t GetIndexCount() const { return m_Indices.size(); }

        uint32_t GetVertexCount() const { return m_Vertices.size(); }
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        GraphicsContext* m_GraphicsContext;

        std::unique_ptr<IVertexBuffer> m_VertexBuffer;
        std::unique_ptr<IIndexBuffer> m_IndexBuffer;
    };
}
