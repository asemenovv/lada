#pragma once

#include <memory>

#include "ApplicationBase.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class DemoApp : public ApplicationBase {
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
    Renderer m_Renderer;
    float m_R = 0.0f;
    float m_Increment = 0.01f;
public:
    DemoApp(): ApplicationBase("LADA Engine", 1280, 960) {}
    ~DemoApp();
protected:
    void Init();
    void BeforeRender();
    void Render(float frameRate);
    void AfterRender();
    void CleanUp();
};
