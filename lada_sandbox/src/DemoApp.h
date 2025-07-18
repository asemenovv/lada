#pragma once

#include <LADA.h>

class DemoApp final :   public Lada::App::Application {
    float m_R = 0.0f;
    float m_Increment = 0.001f;
public:
    DemoApp();
protected:
    void OnDebugUIRender(Lada::App::DebugUIManager* manager) override;
};
