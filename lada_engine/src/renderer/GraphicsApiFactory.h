#pragma once

#include <memory>

#include "GraphicsContext.h"

namespace Lada {
    enum class GraphicAPI {
        VULKAN = 0,
        OPENGL = 1,
    };

    class GraphicsApiFactory {
    public:
        explicit GraphicsApiFactory(const GraphicAPI graphicAPI) : m_GraphicAPI(graphicAPI) {
        }

        [[nodiscard]] std::shared_ptr<GraphicsContext> CreateContext(const std::shared_ptr<Window> &window) const;

        [[nodiscard]] GraphicAPI GetAPI() const { return m_GraphicAPI; }

    private:
        GraphicAPI m_GraphicAPI;
    };
}
