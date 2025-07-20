#pragma once

#include <LADA.h>

class DemoApp final : public Lada::App::Application {
    float m_R = 0.0f;
    float m_Increment = 0.001f;
public:
    DemoApp();
    ~DemoApp() override = default;
private:
    Lada::Render::ImGuiLayer* m_ImGuiLayer;
};
