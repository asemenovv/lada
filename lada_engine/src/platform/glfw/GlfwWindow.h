#pragma once

#include <string>

#include "app/Window.h"
#include "events/Event.h"
#include "events/EventManager.h"

struct GLFWwindow;

namespace Lada {
    class GlfwWindow final : public Window {
    public:
        using WindowEventCallbackFn = std::function<void(const Event&)>;

        GlfwWindow(GraphicAPI graphicApi, const std::string &title, int width, int height,
            std::shared_ptr<EventManager>& eventManager);
        ~GlfwWindow() override = default;

        void OnUpdate() const override;
        void SetVSync(bool enabled) override;
        void Close() const override;

        void* GetNativeWindow() override { return m_Window; }

        [[nodiscard]] WindowSize GetPixelsSize() override;
    private:
        GLFWwindow* m_Window;

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
