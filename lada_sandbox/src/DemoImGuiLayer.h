#pragma once
#include "LADA.h"


class DemoImGuiLayer final : public Lada::Render::ImGuiLayer {
public:
    void OnAttach(Lada::App::LayerContext *context) override;

    void RenderElements(const ImGuiIO& io, Lada::App::LayerContext* context) override;
private:
    bool m_WindowPositionIsSet = false;
};
