#include "ldpch.h"
#include "Application.h"
#include "GlCall.h"
#include "renderer/Renderer.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"

namespace Lada::App {
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        m_LayerContext = new LayerContext();
        m_LayerStack = new LayerStack(m_LayerContext);
        if (s_Instance != nullptr) {
            LD_CORE_CRITICAL("Application already initialized!");
            return;
        }
        s_Instance = this;
        m_EventManager = new Event::EventManager();
        m_Window = new Window(title, width, height, m_EventManager);
        m_Renderer = std::make_shared<Lada::Render::Renderer>(*m_Window);

        if (const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !status) {
            LD_CORE_CRITICAL("GLAD could not be initialized");
        }

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        m_EventManager->BIND_HANDLER(Event::WindowCloseEvent, Application::OnWindowCloseEvent);
        SubscribeLayersOnEvents();

        m_EventManager->BIND_HANDLER(Event::WindowResizeEvent, Application::OnWindowResizeEvent);
    }

    Application::~Application() {
        delete m_LayerStack;
        delete m_LayerContext;
        delete m_EventManager;
        delete m_Window;
    }

    bool Application::OnWindowCloseEvent(const Event::WindowCloseEvent& event) {
        this->Shutdown();
        return true;
    }

    bool Application::OnWindowResizeEvent(const Event::WindowResizeEvent &event) {
        glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return true;
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer *layer : *m_LayerStack) {
                layer->OnUpdate(m_LayerContext);
            }
            m_Renderer->BeginFrame();
            for (Layer* layer : *m_LayerStack) {
                layer->OnRender(m_LayerContext, m_Renderer);
            }
            m_Renderer->EndFrame();
            m_Window->OnUpdate();
        }
    }

    void Application::Shutdown() {
        m_Window->Close();
        m_Running = false;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack->PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack->PushOverlay(layer);
    }

    void Application::PopLayer(const Layer *layer) {
        m_LayerStack->PopLayer(layer);
    }

    void Application::PopOverlay(Layer *layer) {
        m_LayerStack->PopOverlay(layer);
    }

    void Application::SubscribeLayersOnEvents() {
        m_EventManager->RegisterGlobalHandler([this](Event::Event& event) {
            for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
                (*--it)->OnEvent(event, m_LayerContext);
                if (event.IsHandled())
                    break;
            }
            return true;
        });
    }
}
