#include "Application.h"

#include <utility>

#include "render/Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Log.h"
#include "events/ApplicationEvent.h"

namespace lada::app {
    Application::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        m_EventManager = new event::EventManager();
        m_Window = new Window(title, width, height, m_EventManager);
    }

    Application::~Application() {
        delete m_EventManager;
        delete m_Window;
    }

    void Application::Run() {
        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK) {
            LD_CORE_CRITICAL("GLEW could not be initialized");
        }

        GL_CALL(const char* glVersion = (const char*)glGetString(GL_VERSION));
        LD_CORE_INFO("OpenGL version is: {0}", glVersion);

        Init();

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        ImGui::CreateContext();
        const ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(m_Window->m_Window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 330");

        while (!m_Window->ShouldClose()) {
            BeforeRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            OnRender();
            OnImGuiRender(io.Framerate);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            AfterRender();

            m_Window->SwapBuffers();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        CleanUp();
    }

    void Application::Init() {}
    void Application::BeforeRender() {}
    void Application::OnRender() {}
    void Application::OnImGuiRender(float) {}
    void Application::AfterRender() {}
    void Application::CleanUp() {}
}
