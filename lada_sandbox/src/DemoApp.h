#pragma once

#include <LADA.h>

#include "DemoContext.h"

class DemoApp final :   public Lada::App::Application<Context> {
    float m_R = 0.0f;
    float m_Increment = 0.001f;
public:
    DemoApp();
    ~DemoApp();
protected:
    Context& CreateContext() override;
private:
    Context* m_Context;
    Lada::Render::ImGuiLayer<Context>* m_ImGuiLayer;
};
