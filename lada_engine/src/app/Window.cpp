#include "Window.h"

#include "Log.h"
#include "events/ApplicationEvent.h"

namespace lada::app {
     Window::Window(const std::string& title, const int width, const int height, event::EventManager* eventManager)
         : m_EventManager(eventManager) {
        if (!glfwInit())
            LD_CORE_CRITICAL("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

         m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
         if (!m_Window) {
             LD_CORE_CRITICAL("Failed to create GLFW window");
             glfwTerminate();
         }

         glfwSetWindowUserPointer(m_Window, this);
         glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
         glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

         glfwMakeContextCurrent(m_Window);
    }

    Window::~Window() {
         glfwDestroyWindow(m_Window);
         glfwTerminate();
     }

    bool Window::ShouldClose() const {
         return glfwWindowShouldClose(m_Window);
    }

    void Window::SwapBuffers() const {
         glfwSwapBuffers(m_Window);
         glfwPollEvents();
    }

    void Window::WindowCloseCallback(GLFWwindow* glfwWindow) {
         const auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
         if (!window) return;

         const event::WindowCloseEvent event;
         window->m_EventManager->HandleEvent(event);
     }

    void Window::FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height) {
         const auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
         if (!window) return;

         const event::WindowResizeEvent event(width, height);
         window->m_EventManager->HandleEvent(event);
     }
}
