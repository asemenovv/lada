#pragma once
#include <memory>

namespace Lada {
    class Window;

    enum class GraphicAPI {
        VULKAN = 0,
        OPENGL = 1,
    };

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static std::shared_ptr<GraphicsContext> Create(const std::shared_ptr<Window>& window, GraphicAPI api);
    };
}
