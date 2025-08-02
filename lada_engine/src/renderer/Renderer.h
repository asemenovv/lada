#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "platform/glfw/GlfwWindow.h"
#include "glm/vec4.hpp"

namespace Lada::Render {
    class Model;

    class Renderer {
    public:
        explicit Renderer(std::shared_ptr<Window>& window);

        void Init();

        void Shutdown();

        void BeginFrame();

        void Submit(std::shared_ptr<Model> model) const;

        void EndFrame();

        void SetClearColor(const glm::vec4 &color) { m_ClearColor = color; }

        std::shared_ptr<Camera> GetCamera() { return m_Camera; }

    private:
        glm::vec4 m_ClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<Camera> m_Camera;
    };
}
