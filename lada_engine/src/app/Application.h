#pragma once

#include <string>

#include "events/EventManager.h"
#include "../platform/glfw/GlfwWindow.h"
#include "assets/AssetManager.h"
#include "events/ApplicationEvent.h"
#include "layer/LayerContext.h"
#include "layer/LayerStack.h"
#include "renderer/GraphicsContext.h"
#include "renderer/Renderer.h"
#include "renderer/SceneRenderer.h"
#include "scene/Scene.h"

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
        std::unique_ptr<Scene> m_Scene;
        std::unique_ptr<AssetManager> m_AssetManager;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<EventManager> m_EventManager;
        std::unique_ptr<GraphicsContext> m_GraphicsContext;
        std::unique_ptr<LayerStack> m_LayerStack;
        std::unique_ptr<LayerContext> m_LayerContext;
        std::unique_ptr<Render::Renderer> m_Renderer;
        std::unique_ptr<SceneRenderer> m_SceneRenderer;


        static Application* s_Instance;

        void subscribeLayersOnEvents();

        bool onWindowCloseEvent(const WindowCloseEvent& event);

        void loadScene();
    };
}
