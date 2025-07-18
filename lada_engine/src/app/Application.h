#pragma once

#include <string>

#include "DebugUIManager.h"
#include "events/EventManager.h"
#include "Window.h"
#include "imgui/ImGuiLayer.h"
#include "layer/LayerStack.h"

namespace Lada::App {
    class Application {
    public:
        virtual ~Application();
        Application(const std::string &title, int width, int height);
        void Run();
        void Shutdown();
        Window& GetWindow() { return *m_Window; }

        static Application& Get() { return *s_Instance; }
    protected:
        virtual void OnDebugUIRender(DebugUIManager* manager) = 0;
        void PushLayer(Layer *layer);
        void PopLayer(const Layer *layer);
        [[nodiscard]] Event::EventManager* GetEventManager() const { return m_EventManager; }
    private:
        bool m_Running = true;
        Render::ImGuiLayer* m_ImGuiLayer;
        Window* m_Window;
        Event::EventManager* m_EventManager;
        DebugUIManager* m_DebugUIManager;
        LayerStack m_LayerStack;

        static Application* s_Instance;

        void SubscribeLayersOnEvents();
    };
}
