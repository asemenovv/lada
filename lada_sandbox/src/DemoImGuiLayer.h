#pragma once
#include "DemoContext.h"
#include "LADA.h"


class DemoImGuiLayer final : public Lada::Render::ImGuiLayer<Context> {
public:
    void RenderElements(const ImGuiIO& io, Context& context) override;
};
