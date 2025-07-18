#pragma once
#include "LADA.h"

class RenderingLayer final : public Lada::App::Layer {
public:
    RenderingLayer() = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRender() override;
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
