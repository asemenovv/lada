#include "ldpch.h"
#include "Application.h"

#include "render/Renderer.h"
#include "DebugUIManager.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace Lada::App {
    Application::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        m_EventManager = new Event::EventManager();
        m_Window = new Window(title, width, height, m_EventManager);

        if (glewInit() != GLEW_OK) {
            LD_CORE_CRITICAL("GLEW could not be initialized");
        }

        GL_CALL(const char* glVersion = (const char*)glGetString(GL_VERSION));
        LD_CORE_INFO("OpenGL version is: {0}", glVersion);

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        m_DebugUIManager = new DebugUIManager(m_Window);
        m_EventManager->REGISTER_HANDLER(Event::WindowCloseEvent, {
            this->Shutdown();
            return true;
        });
    }

    Application::~Application() {
        delete m_DebugUIManager;
        delete m_EventManager;
        delete m_Window;
        Application::CleanUp();
    }

    void Application::Run() {
        Init();
        while (m_Running) {
            BeforeRender();
            m_DebugUIManager->BeforeRender();

            OnRender();
            m_DebugUIManager->Begin();
            OnDebugUIRender(m_DebugUIManager);
            m_DebugUIManager->End();

            m_DebugUIManager->AfterRender();
            AfterRender();
            m_Window->Update();
        }
    }

    void Application::Shutdown() {
        m_Window->Close();
        m_Running = false;
    }

    void Application::Init() {}
    void Application::BeforeRender() {}
    void Application::AfterRender() {}
    void Application::CleanUp() {}
}
