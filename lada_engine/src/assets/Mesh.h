#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>

#include "Asset.h"

namespace Lada {
    class Mesh final : public Asset {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec3 color;
            glm::vec2 uv;

            bool operator==(const Vertex &other) const {
                return position == other.position && normal == other.normal && color == other.color && uv == other.uv;
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

        explicit Mesh(const AssetID &id);

        ~Mesh() override = default;

        size_t VerticesCount() const;

        void AddVertex(const Vertex &vertex);

        void AddIndex(uint32_t vertexIndex);

    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
    };
}
