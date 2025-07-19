#include "DemoImGuiLayer.h"

void DemoImGuiLayer::RenderElements(const ImGuiIO &io, Context& context) {
    float r = 0.0;
    ImGuiLayer::RenderElements(io, context);
    ImGui::SliderFloat("Rotation", &r, 0.0f, 1.0f);
}
