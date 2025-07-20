#pragma once
#include "LADA.h"

class RenderingLayer final : public Lada::App::Layer {
public:
    RenderingLayer() = default;
    void OnAttach(Lada::App::LayerContext* context) override;
    void OnDetach(Lada::App::LayerContext* context) override;
    void OnUpdate(Lada::App::LayerContext* context) override;
    void OnRender(Lada::App::LayerContext* context) override;
private:
    std::unique_ptr<Lada::Render::VertexArray> m_VertexArray;
    std::unique_ptr<Lada::Render::IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Lada::Render::Shader> m_Shader;
    std::unique_ptr<Lada::Render::Texture> m_Texture;
    std::unique_ptr<Lada::Render::VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Lada::Render::VertexBufferLayout> m_VertexBufferLayout;
    Lada::Render::Renderer m_Renderer;
};
