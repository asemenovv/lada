#pragma once

#include <string>

#include "events/EventManager.h"

struct GLFWwindow;

namespace lada::app {
    class Window {
    friend class DebugUIManager;
    public:
        Window(const std::string &title, int width, int height, event::EventManager* eventManager);
        ~Window();

        [[nodiscard]] bool ShouldClose() const;
        void SwapBuffers() const;
    private:
        GLFWwindow* m_Window;
        event::EventManager* m_EventManager;

        static void WindowCloseCallback(GLFWwindow* glfwWindow);
        static void FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
    };
}
