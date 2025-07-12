#include "DemoApp.h"

#include "Texture.h"
#include "VertexBufferLayout.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"

DemoApp::~DemoApp() {
}


void DemoApp::Init() {
    constexpr float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
    };
    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
   };

    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CALL(glEnable(GL_BLEND));

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(2);
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Shader>("./res/shaders/Basic.glsl");
    m_Shader->Bind();
    m_Texture = std::make_unique<Texture>("./res/textures/aquarium.png");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
}

void DemoApp::BeforeRender() {
    const glm::mat4 proj = glm::ortho(-2.0f, 2.0f,-1.5f, 1.5f,-1.0f, 1.0f);
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, 0.0f));
    const glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f * m_R), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * view * model;
    m_Shader->Bind();
    m_Texture->Bind();
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    m_Shader->SetUniform4f("u_Color", m_R, 0.3f, 0.8f, 1.0f);
    m_Renderer.Clear();
}

void DemoApp::Render(const float frameRate) {
    m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    {
        ImGui::Begin("Lada::Debug");
        ImGui::SliderFloat("Rotation", &m_R, 0.0f, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / frameRate, frameRate);
        ImGui::End();
    }
}

void DemoApp::AfterRender() {
    if (m_R > 1.0f || m_R < 0.0f) {
        m_Increment = -m_Increment;
    }
    m_R += m_Increment;
}

void DemoApp::CleanUp() {
    ;
}
