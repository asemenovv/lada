#pragma once

#include <string>

#include "events/EventManager.h"
#include "../platform/glfw/GlfwWindow.h"
#include "events/ApplicationEvent.h"
#include "layer/LayerContext.h"
#include "layer/LayerStack.h"
#include "renderer/Renderer.h"
#include "renderer/SwapChain.h"

namespace Lada::App {
    class Application {
    public:
        Application(const std::string &title, int width, int height);
        virtual ~Application() = default;
        void Run();
        void Shutdown();
        [[nodiscard]] Window& GetWindow() const { return *m_Window; }
        static Application& Get() { return *s_Instance; }
    protected:
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopLayer(const Layer *layer);
        void PopOverlay(Layer *layer);
        [[nodiscard]] EventManager& GetEventManager() const { return *m_EventManager; }
    private:
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<EventManager> m_EventManager;
        std::unique_ptr<GraphicsContext> m_GraphicsContext;
        std::unique_ptr<LayerStack> m_LayerStack;
        std::unique_ptr<LayerContext> m_LayerContext;
        std::shared_ptr<Render::Renderer> m_Renderer;
        std::shared_ptr<SwapChain> m_SwapChain;


        static Application* s_Instance;

        void SubscribeLayersOnEvents();

        bool OnWindowCloseEvent(const WindowCloseEvent& event);
        bool OnWindowResizeEvent(const WindowResizeEvent& event);
    };
}
