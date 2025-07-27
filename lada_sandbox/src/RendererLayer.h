#pragma once
#include "LADA.h"
#include "renderer/Renderer.h"

class RendererLayer final : public Lada::App::Layer {
public:
    void OnAttach(Lada::App::LayerContext *context) override;

    void OnUpdate(Lada::App::LayerContext *context) override;

    void OnRender(Lada::App::LayerContext *context) override;
private:
    std::shared_ptr<Lada::Render::Material> m_Material;
    std::shared_ptr<Lada::Render::Mesh> m_Square;
    std::shared_ptr<Lada::Render::Renderer> m_Renderer;
};
