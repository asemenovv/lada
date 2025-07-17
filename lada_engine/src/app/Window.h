#pragma once

#include <string>

#include "events/Event.h"
#include "events/EventManager.h"

struct GLFWwindow;

namespace lada::app {
    class Window {
    friend class DebugUIManager;
    public:
        using WindowEventCallbackFn = std::function<void(const event::Event&)>;

        Window(const std::string &title, int width, int height, event::EventManager* eventManager);
        ~Window() = default;

        void Update() const;
        void SetVSync(bool enabled);
        void Close() const;
    private:
        GLFWwindow* m_Window;
        event::EventManager* m_EventManager;

        static void WindowCloseCallback(GLFWwindow* glfwWindow);
        static void FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
        static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
        static void CharCallback(GLFWwindow* glfwWindow, unsigned int keycode);
        static void MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
        static void ScrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset);
        static void CursorPosCallback(GLFWwindow* glfwWindow, double xPos, double yPos);

        void SubscribeToEvents();
    };
}
