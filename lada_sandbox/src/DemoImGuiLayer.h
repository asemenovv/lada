#pragma once
#include "LADA.h"


class DemoImGuiLayer final : public Lada::Render::ImGuiLayer {
public:
    void RenderElements(const ImGuiIO& io, Lada::App::LayerContext* context) override;
};
