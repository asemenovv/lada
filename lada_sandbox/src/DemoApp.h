#pragma once

#include <memory>
#include <LADA.h>

class ExampleLayer final : public Lada::App::Layer {
public:
    ExampleLayer(): Layer("ExampleLayer") {
    }

    void OnAttach() override {
        LD_INFO("OnAttach");
    }

    void OnUpdate() override {
        LD_INFO("OnUpdate");
    }

    void OnRender() override {
        LD_INFO("OnRender");
    }

    void OnDetach() override {
        LD_INFO("OnDetach");
    }

    void OnEvent(const Lada::Event::Event &event) override {
        LD_INFO("OnEvent {}", event.ToString());
    }
};

class DemoApp final :   public Lada::App::Application {
    std::unique_ptr<Lada::Render::VertexArray> m_VertexArray;
    std::unique_ptr<Lada::Render::IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Lada::Render::Shader> m_Shader;
    std::unique_ptr<Lada::Render::Texture> m_Texture;
    std::unique_ptr<Lada::Render::VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Lada::Render::VertexBufferLayout> m_VertexBufferLayout;
    Lada::Render::Renderer m_Renderer;
    float m_R = 0.0f;
    float m_Increment = 0.001f;
public:
    DemoApp(): Application("LADA Engine", 640, 480) {}
protected:
    void Init() override;
    void BeforeRender() override;
    void OnRender() override;
    void OnDebugUIRender(Lada::App::DebugUIManager* manager) override;
    void AfterRender() override;
};
