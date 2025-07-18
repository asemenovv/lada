#pragma once

#include <string>

#include "DebugUIManager.h"
#include "events/EventManager.h"
#include "Window.h"
#include "layer/LayerStack.h"

namespace Lada::App {
    class Application {
    public:
        virtual ~Application();
        Application(const std::string &title, int width, int height);
        void Run();
        void Shutdown();
    protected:
        virtual void BeforeRender() {};
        virtual void OnDebugUIRender(DebugUIManager* manager) = 0;
        void PushLayer(Layer *layer);
        void PopLayer(const Layer *layer);
        [[nodiscard]] Event::EventManager* GetEventManager() const { return m_EventManager; }
    private:
        bool m_Running = true;
        Window* m_Window;
        Event::EventManager* m_EventManager;
        DebugUIManager* m_DebugUIManager;
        LayerStack m_LayerStack;

        void SubscribeLayersOnEvents();
    };
}
