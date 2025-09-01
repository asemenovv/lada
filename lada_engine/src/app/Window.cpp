#include "Window.h"

#include "platform/glfw/GlfwWindow.h"

namespace Lada {
    Window::Window(const int width, const int height, std::shared_ptr<EventManager>& eventManager) : m_Width(width), m_Height(height),
        m_EventManager(eventManager) {
    }

    std::shared_ptr<Window> Window::Create(std::string title, int width, int height,
                                           std::shared_ptr<EventManager> &eventManager, const GraphicAPI api) {
        switch (api) {
            case GraphicAPI::OPENGL:
                return std::make_shared<GlfwWindow>(GraphicAPI::OPENGL, title, width, height, eventManager);
            case GraphicAPI::VULKAN:
                return std::make_shared<GlfwWindow>(GraphicAPI::VULKAN, title, width, height, eventManager);
            default:
                throw std::runtime_error("Unsupported API");
        }
    }
}
