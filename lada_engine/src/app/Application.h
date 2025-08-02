#pragma once

#include <string>

#include "events/EventManager.h"
#include "../platform/glfw/GlfwWindow.h"
#include "events/ApplicationEvent.h"
#include "layer/LayerContext.h"
#include "layer/LayerStack.h"
#include "renderer/Renderer.h"

namespace Lada::App {
    class Application {
    public:
        Application(const std::string &title, int width, int height);
        virtual ~Application();
        void Run();
        void Shutdown();
        std::shared_ptr<Window> GetWindow() const { return m_Window; }
        static Application& Get() { return *s_Instance; }
    protected:
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopLayer(const Layer *layer);
        void PopOverlay(Layer *layer);
        std::shared_ptr<EventManager> GetEventManager() const { return m_EventManager; }
    private:
        bool m_Running = true;
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<EventManager> m_EventManager;
        LayerStack* m_LayerStack;
        LayerContext* m_LayerContext;
        std::shared_ptr<Render::Renderer> m_Renderer;

        static Application* s_Instance;

        void SubscribeLayersOnEvents();

        bool OnWindowCloseEvent(const WindowCloseEvent& event);
        bool OnWindowResizeEvent(const WindowResizeEvent& event);
    };
}
