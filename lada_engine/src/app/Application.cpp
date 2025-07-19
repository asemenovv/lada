#include "ldpch.h"
#include "Application.h"
#include "render/Renderer.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"

namespace Lada::App {
    template<typename T>
    Application<T>* Application<T>::s_Instance = nullptr;

    template<typename T>
    Application<T>::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        if (s_Instance != nullptr) {
            LD_CORE_CRITICAL("Application already initialized!");
            return;
        }
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

        m_EventManager->BIND_HANDLER(Event::WindowCloseEvent, Application::OnWindowCloseEvent);
        SubscribeLayersOnEvents();

        m_EventManager->BIND_HANDLER(Event::WindowResizeEvent, Application::OnWindowResizeEvent);
    }

    template<typename T>
    void Application<T>::Run() {
        Run(CreateContext());
    }

    template<typename T>
    bool Application<T>::OnWindowCloseEvent(const Event::WindowCloseEvent& event) {
        this->Shutdown();
        return true;
    }

    template<typename T>
    bool Application<T>::OnWindowResizeEvent(const Event::WindowResizeEvent &event) {
        glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return true;
    }

    template<typename T>
    Application<T>::~Application() {
        delete m_EventManager;
        delete m_Window;
    }

    template<typename T>
    void Application<T>::Run(T& context) {
        while (m_Running) {
            for (Layer<T> *layer : m_LayerStack) {
                layer->OnUpdate(context);
            }
            for (Layer<T>* layer : m_LayerStack) {
                layer->OnRender(context);
            }
            m_Window->OnUpdate();
        }
    }

    template<typename T>
    void Application<T>::Shutdown() {
        m_Window->Close();
        m_Running = false;
    }

    template<typename T>
    void Application<T>::PushLayer(Layer<T> *layer) {
        m_LayerStack.PushLayer(layer);
    }

    template<typename T>
    void Application<T>::PopLayer(const Layer<T> *layer) {
        m_LayerStack.PopLayer(layer);
    }

    template<typename T>
    void Application<T>::SubscribeLayersOnEvents() {
        m_EventManager->RegisterGlobalHandler([this](Event::Event& event) {
            for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
                (*--it)->OnEvent(event);
                if (event.IsHandled())
                    break;
            }
            return true;
        });
    }
}
