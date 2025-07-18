#include "ldpch.h"
#include "Window.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace Lada::App {
    Window::Window(const std::string &title, const int width, const int height, Event::EventManager* eventManager):
        m_EventManager(eventManager), m_Width(width), m_Height(height) {
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

        SubscribeToEvents();

        glfwMakeContextCurrent(m_Window);
        eventManager->REGISTER_HANDLER(Lada::Event::WindowResizeEvent, {
            m_Width = event.GetWidth();
            m_Height = event.GetHeight();
            return true;
        });
    }

    void Window::OnUpdate() const {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
    }

    void Window::Close() const {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::SubscribeToEvents() {
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        glfwSetKeyCallback(m_Window, KeyCallback);
        glfwSetCharCallback(m_Window, CharCallback);
        glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
        glfwSetScrollCallback(m_Window, ScrollCallback);
        glfwSetCursorPosCallback(m_Window, CursorPosCallback);
    }

    void Window::WindowCloseCallback(GLFWwindow *glfwWindow) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for WindowClose event");
            return;
        }

        const Event::WindowCloseEvent event;
        window->m_EventManager->HandleEvent(event);
    }

    void Window::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for FramebufferSize event");
            return;
        }

        const Event::WindowResizeEvent event(width, height);
        window->m_EventManager->HandleEvent(event);
    }

    void Window::KeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Key event");
            return;
        }

        switch (action) {
            case GLFW_PRESS: {
                const Event::KeyPressedEvent event(key, 0);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_RELEASE: {
                const Event::KeyReleasedEvent event(key);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_REPEAT: {
                const Event::KeyPressedEvent event(key, true);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            default:
                LD_CORE_ERROR("Undefined key action {0} in callback", action);
        }
    }

    void Window::CharCallback(GLFWwindow *glfwWindow, unsigned int keycode) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Char event");
            return;
        }

        Event::KeyTypedEvent event(keycode);
        window->m_EventManager->HandleEvent(event);
    }

    void Window::MouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for MouseButton event");
            return;
        }

        switch (action) {
            case GLFW_PRESS: {
                const Event::MouseButtonPressedEvent event(button);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_RELEASE: {
                const Event::MouseButtonReleasedEvent event(button);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            default:
                LD_CORE_ERROR("Undefined mouse button action {0} in callback", action);
        }
    }

    void Window::ScrollCallback(GLFWwindow *glfwWindow, double xOffset, double yOffset) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Scroll event");
            return;
        }

        Event::MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        window->m_EventManager->HandleEvent(event);
    }

    void Window::CursorPosCallback(GLFWwindow *glfwWindow, double xPos, double yPos) {
        const auto *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Cursor event");
            return;
        }

        const Event::MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        window->m_EventManager->HandleEvent(event);
    }
}
