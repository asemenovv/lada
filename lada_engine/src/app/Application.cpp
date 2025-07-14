#include "Application.h"

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../render/Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Log.h"

namespace lada::app {
    Application::Application(const std::string& title, const int width, const int height)
        : m_Window(nullptr), m_Width(width), m_Height(height), m_Title(title) {}

    void Application::Run() {
        if (!glfwInit())
            std::cerr << "Failed to initialize GLFW" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

        if (!m_Window) {
            glfwTerminate();
            std::cerr << "Failed to create GLFW window" << std::endl;
        }

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK) {
            std::cerr << "GLEW could not be initialized" << std::endl;
        }

        GL_CALL(const char* glVersion = (const char*)glGetString(GL_VERSION));
        LD_INFO("OpenGL version is: {0}", glVersion);

        Init();

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        ImGui::CreateContext();
        const ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 330");

        while (!glfwWindowShouldClose(m_Window)) {
            BeforeRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            OnRender();
            OnImGuiRender(io.Framerate);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            AfterRender();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        CleanUp();

        glfwTerminate();
    }

    void Application::Init() {}
    void Application::BeforeRender() {}
    void Application::OnRender() {}
    void Application::OnImGuiRender(float) {}
    void Application::AfterRender() {}
    void Application::CleanUp() {}
}
