#include "ldpch.h"
#include "Application.h"
#include "render/Renderer.h"
#include "DebugUIManager.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"

namespace Lada::App {
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        s_Instance = this;
        m_EventManager = new Event::EventManager();
        m_Window = new Window(title, width, height, m_EventManager);

        if (const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !status) {
            LD_CORE_CRITICAL("GLAD could not be initialized");
        }

        GL_CALL(const char* glVersion = (const char*)glGetString(GL_VERSION));
        LD_CORE_INFO("OpenGL version is: {0}", glVersion);

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        // m_DebugUIManager = new DebugUIManager(m_Window);
        m_EventManager->REGISTER_HANDLER(Event::WindowCloseEvent, {
            this->Shutdown();
            return true;
        });
        SubscribeLayersOnEvents();

        m_ImGuiLayer = new Render::ImGuiLayer();
        PushLayer(m_ImGuiLayer);
    }

    Application::~Application() {
        delete m_DebugUIManager;
        delete m_EventManager;
        delete m_Window;
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate();
            }
            for (Layer* layer : m_LayerStack) {
                layer->OnRender();
            }
            m_Window->OnUpdate();
        }
    }

    void Application::Shutdown() {
        m_Window->Close();
        m_Running = false;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PopLayer(const Layer *layer) {
        m_LayerStack.PopLayer(layer);
    }

    void Application::SubscribeLayersOnEvents() {
        m_EventManager->RegisterGlobalHandler([this](const Event::Event& event) {
            for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
                (*--it)->OnEvent(event);
                if (event.IsHandled())
                    break;
            }
            return true;
        });
    }
}
