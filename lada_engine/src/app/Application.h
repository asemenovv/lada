#pragma once

#include <string>

#include "DebugUIManager.h"
#include "events/EventManager.h"
#include "Window.h"

namespace lada::app {
    class Application {
    public:
        virtual ~Application();
        Application(const std::string &title, int width, int height);
        void Run();
    protected:
        virtual void Init();
        virtual void BeforeRender();
        virtual void OnRender() = 0;
        virtual void OnDebugUIRender(lada::app::DebugUIManager* manager) = 0;
        virtual void AfterRender();
        virtual void CleanUp();
        [[nodiscard]] event::EventManager* GetEventManager() const { return m_EventManager; }
    private:
        Window* m_Window;
        event::EventManager* m_EventManager;
        DebugUIManager* m_DebugUIManager;
    };
}
