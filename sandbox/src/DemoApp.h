#pragma once

#include <memory>

#include "app/ApplicationBase.h"
#include "render/IndexBuffer.h"
#include "render/Renderer.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexArray.h"
#include "render/VertexBufferLayout.h"

class DemoApp : public lada::app::ApplicationBase {
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
    DemoApp(): ApplicationBase("LADA Engine", 1280, 960) {}
    ~DemoApp();
protected:
    void Init();
    void BeforeRender();
    void OnRender();
    void OnImGuiRender(float frameRate);
    void AfterRender();
    void CleanUp();
};
