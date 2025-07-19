#pragma once

#include <string>

#include "events/EventManager.h"
#include "Window.h"
#include "events/ApplicationEvent.h"
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
        void PushLayer(Layer *layer);
        void PopLayer(const Layer *layer);
        [[nodiscard]] Event::EventManager* GetEventManager() const { return m_EventManager; }
    private:
        bool m_Running = true;
        Window* m_Window;
        Event::EventManager* m_EventManager;
        LayerStack m_LayerStack;

        static Application* s_Instance;

        void SubscribeLayersOnEvents();

        bool OnWindowCloseEvent(const Event::WindowCloseEvent& event);
        bool OnWindowResizeEvent(const Event::WindowResizeEvent& event);
    };
}
