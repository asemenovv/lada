#include "DemoImGuiLayer.h"

#include "ContextVars.h"

void DemoImGuiLayer::OnAttach(Lada::App::LayerContext *context) {
    ImGuiLayer::OnAttach(context);
}

void DemoImGuiLayer::RenderElements(const ImGuiIO &io, Lada::App::LayerContext* context) {
    if (!m_WindowPositionIsSet) {
        ImGui::SetNextWindowPos(ImGui::GetWindowPos());
    }
    ImGui::Begin("Lada::Debug");
    ImGuiLayer::RenderElements(io, context);
    ImGui::SliderFloat("Rotation", context->GetF(SQUARE_ROTATION), 0.0f, 1.0f);
    ImGui::End();

    if (!m_WindowPositionIsSet) {
        ImGui::SetNextWindowPos(ImGui::GetWindowPos());
        m_WindowPositionIsSet = true;
    }
    ImGui::Begin("Lada::Another Window");
    ImGui::Checkbox("Reset Position: ", &m_WindowPositionIsSet);
    ImGui::End();
}
