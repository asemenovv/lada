#pragma once

#include <memory>
#include <LADA.h>

class DemoApp final : public lada::app::Application {
    std::unique_ptr<lada::render::VertexArray> m_VertexArray;
    std::unique_ptr<lada::render::IndexBuffer> m_IndexBuffer;
    std::unique_ptr<lada::render::Shader> m_Shader;
    std::unique_ptr<lada::render::Texture> m_Texture;
    std::unique_ptr<lada::render::VertexBuffer> m_VertexBuffer;
    std::unique_ptr<lada::render::VertexBufferLayout> m_VertexBufferLayout;
    lada::render::Renderer m_Renderer;
    float m_R = 0.0f;
    float m_Increment = 0.001f;
public:
    DemoApp(): Application("LADA Engine", 640, 480) {}
protected:
    void Init() override;
    void BeforeRender() override;
    void OnRender() override;
    void OnImGuiRender(float frameRate) override;
    void AfterRender() override;
};
