#pragma once
#include "app/Window.h"
#include "glm/vec4.hpp"

namespace Lada::Render {
    class Renderer {
    public:
        Renderer(App::Window* window);

        void Init();
        void Shutdown();

        void BeginFrame();
        void EndFrame();

        void SetClearColor(const glm::vec4& color) { m_ClearColor = color; }
    private:
        glm::vec4 m_ClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        App::Window* m_Window;
    };
}
