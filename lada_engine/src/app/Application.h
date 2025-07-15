#pragma once

#include <string>

#include "../events/EventBus.h"

struct GLFWwindow;

namespace lada::app {
    class Application {
    public:
        virtual ~Application();
        Application(std::string  title, int width, int height);
        void Run();
    protected:
        virtual void Init();
        virtual void BeforeRender();
        virtual void OnRender();
        virtual void OnImGuiRender(float frameRate);
        virtual void AfterRender();
        virtual void CleanUp();
        [[nodiscard]] event::EventBus* GetEventBus() const { return m_EventBus; }
    private:
        GLFWwindow* m_Window;
        int m_Width, m_Height;
        std::string m_Title;
        event::EventBus* m_EventBus;

        void WindowCloseCallback(GLFWwindow* window) const;
    };
}
