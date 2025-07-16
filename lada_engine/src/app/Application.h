#pragma once

#include <string>

#include "GL/glew.h"
#include "Window.h"
#include "events/EventManager.h"

struct GLFWwindow;

namespace lada::app {
    class Application {
    public:
        virtual ~Application();
        Application(const std::string &title, int width, int height);
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
        Window* m_Window;
        event::EventManager* m_EventManager;
    };
}
