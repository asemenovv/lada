#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "CommandBuffer.h"
#include "events/ApplicationEvent.h"
#include "platform/glfw/GlfwWindow.h"
#include "glm/vec4.hpp"

namespace Lada {
    class GraphicsContext;
}

namespace Lada::Render {
    class Model;

    class Renderer {
    public:
        explicit Renderer(const Window& window, GraphicsContext* graphicsContext, EventManager* eventManager);

        void Init();

        void Shutdown();

        CommandBuffer* BeginFrame();

        void Submit(const std::shared_ptr<Model> &model) const;

        void EndFrame();

        void SetClearColor(const glm::vec4 &color) { m_ClearColor = color; }

        std::shared_ptr<Camera> GetCamera() { return m_Camera; }

    private:
        glm::vec4 m_ClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        GraphicsContext* m_GraphicsContext;
        std::shared_ptr<Camera> m_Camera;
        std::vector<std::unique_ptr<CommandBuffer>> m_CommandBuffers;
        uint32_t m_CurrentImageIndex;
        int m_CurrentFrameIndex;
        EventManager* m_EventManager;

        bool OnWindowResizeEvent(const WindowResizeEvent& event) const;
    };
}
