#pragma once
#include "LADA.h"

class RendererLayer final : public Lada::App::Layer {
public:
    void OnAttach(Lada::App::LayerContext& context) override;

    void OnUpdate(Lada::App::LayerContext& context) override;

    void OnRender(Lada::App::LayerContext& context, const std::shared_ptr<Lada::Render::Renderer>& renderer) override;
private:
    std::shared_ptr<Lada::Render::Model> m_Square;
};
