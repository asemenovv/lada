#pragma once

#include <string>

#include "events/EventManager.h"

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
        [[nodiscard]] event::EventManager* GetEventManager() const { return m_EventManager; }
    private:
        GLFWwindow* m_Window;
        int m_Width, m_Height;
        std::string m_Title;
        event::EventManager* m_EventManager;

        static void WindowCloseCallback(GLFWwindow* window);
    };
}
