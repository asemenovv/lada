#include "ldpch.h"
#include "DebugUIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace lada::app {
    DebugUIManager::DebugUIManager(const Window* window) {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window->m_Window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    DebugUIManager::~DebugUIManager() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DebugUIManager::BeforeRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void DebugUIManager::Begin() const {
        ImGui::Begin("Lada::Debug");
    }

    void DebugUIManager::End() const {
        ImGui::End();
    }

    void DebugUIManager::AfterRender() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    float DebugUIManager::FrameRate() {
        const ImGuiIO& io = ImGui::GetIO();
        return io.Framerate;
    }

    void DebugUIManager::Slider(const std::string& label, float *value, const float min, const float max) {
        ImGui::SliderFloat(label.c_str(), value, min, max);
    }

    void DebugUIManager::Text(const char* format, ...) {
        va_list args;
        va_start(args, format);
        ImGui::Text(format, args);
        va_end(args);
    }
}
