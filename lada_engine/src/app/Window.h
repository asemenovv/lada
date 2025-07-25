#pragma once

#include <string>

#include "events/Event.h"
#include "events/EventManager.h"

struct GLFWwindow;

namespace Lada::App {
    class Window {
    friend class DebugUIManager;
    public:
        using WindowEventCallbackFn = std::function<void(const Event::Event&)>;

        Window(const std::string &title, int width, int height, Event::EventManager* eventManager);
        ~Window() = default;

        void OnUpdate() const;
        void SwapBuffers() const;
        void SetVSync(bool enabled);
        void Close() const;
        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }

        [[nodiscard]] GLFWwindow* GetNativeWindow() const { return m_Window; }
    private:
        int m_Width, m_Height;
        GLFWwindow* m_Window;
        Event::EventManager* m_EventManager;

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
