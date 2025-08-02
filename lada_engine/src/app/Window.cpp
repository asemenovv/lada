#include "Window.h"

#include "platform/glfw/GlfwWindow.h"

namespace Lada {
    Window::Window(const int width, const int height, std::shared_ptr<EventManager>& eventManager) : m_Width(width), m_Height(height),
        m_EventManager(eventManager) {
    }

    std::shared_ptr<GraphicsContext> Window::GetGraphicsContext() const {
        return m_GraphicsContext;
    }

    std::shared_ptr<Window> Window::Create(std::string title, int width, int height,
        std::shared_ptr<EventManager> &eventManager) {
        return std::make_shared<GlfwWindow>(title, width, height, eventManager);
    }
}
