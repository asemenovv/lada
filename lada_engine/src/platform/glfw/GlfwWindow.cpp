#include "ldpch.h"
#include "GlfwWindow.h"
#include "app/Logger.h"
#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "GLFW/glfw3.h"

namespace Lada {
    GlfwWindow::GlfwWindow(const std::string &title, const int width, const int height,
                           std::shared_ptr<EventManager>& eventManager)
    : Window(width, height, eventManager) {
        if (!glfwInit())
            LD_CORE_CRITICAL("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            LD_CORE_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
        }
        m_GraphicsContext = GraphicsContext::Create(m_Window);

        SubscribeToEvents();

        m_GraphicsContext->Init();
        eventManager->REGISTER_HANDLER(WindowResizeEvent, {
                                       m_Width = event.GetWidth();
                                       m_Height = event.GetHeight();
                                       return true;
                                       });
    }

    void GlfwWindow::OnUpdate() const {
        glfwPollEvents();
    }

    void GlfwWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
    }

    void GlfwWindow::Close() const {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void GlfwWindow::SubscribeToEvents() {
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        glfwSetKeyCallback(m_Window, KeyCallback);
        glfwSetCharCallback(m_Window, CharCallback);
        glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
        glfwSetScrollCallback(m_Window, ScrollCallback);
        glfwSetCursorPosCallback(m_Window, CursorPosCallback);
    }

    void GlfwWindow::WindowCloseCallback(GLFWwindow *glfwWindow) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for WindowClose event");
            return;
        }

        WindowCloseEvent event;
        window->m_EventManager->HandleEvent(event);
    }

    void GlfwWindow::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for FramebufferSize event");
            return;
        }

        WindowResizeEvent event(width, height);
        window->m_EventManager->HandleEvent(event);
    }

    void GlfwWindow::KeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Key event");
            return;
        }

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, true);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            default:
                LD_CORE_ERROR("Undefined key action {0} in callback", action);
        }
    }

    void GlfwWindow::CharCallback(GLFWwindow *glfwWindow, unsigned int keycode) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Char event");
            return;
        }

        KeyTypedEvent event(keycode);
        window->m_EventManager->HandleEvent(event);
    }

    void GlfwWindow::MouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for MouseButton event");
            return;
        }

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                window->m_EventManager->HandleEvent(event);
                break;
            }
            default:
                LD_CORE_ERROR("Undefined mouse button action {0} in callback", action);
        }
    }

    void GlfwWindow::ScrollCallback(GLFWwindow *glfwWindow, double xOffset, double yOffset) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Scroll event");
            return;
        }

        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        window->m_EventManager->HandleEvent(event);
    }

    void GlfwWindow::CursorPosCallback(GLFWwindow *glfwWindow, double xPos, double yPos) {
        const auto *window = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(glfwWindow));
        if (!window) {
            LD_CORE_ERROR("Window is not set for Cursor event");
            return;
        }

        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        window->m_EventManager->HandleEvent(event);
    }
}
