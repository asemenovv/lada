#pragma once
#include "DemoContext.h"
#include "LADA.h"

class RenderingLayer final : public Lada::App::Layer<Context> {
public:
    RenderingLayer() = default;
    void OnAttach(Context& context) override;
    void OnDetach(Context& context) override;
    void OnUpdate(Context& context) override;
    void OnRender(Context& context) override;
private:
    std::unique_ptr<Lada::Render::VertexArray> m_VertexArray;
    std::unique_ptr<Lada::Render::IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Lada::Render::Shader> m_Shader;
    std::unique_ptr<Lada::Render::Texture> m_Texture;
    std::unique_ptr<Lada::Render::VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Lada::Render::VertexBufferLayout> m_VertexBufferLayout;
    Lada::Render::Renderer m_Renderer;
    float m_R = 0.0f;
    float m_Increment = 0.001f;
};
