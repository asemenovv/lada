#include "DemoApp.h"

#include <filesystem>
#include <string>

std::string workingDir() {
    const std::filesystem::path currentPath = std::filesystem::current_path()
        .parent_path()
        .parent_path();
    std::string currentDirectory = currentPath.string();
    return currentDirectory;
}

void DemoApp::Init() {
    std::string workingDirectory = workingDir();
    LD_INFO("Working directory is {0}", workingDirectory);
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

    m_VertexArray = std::make_unique<lada::render::VertexArray>();
    m_VertexBuffer = std::make_unique<lada::render::VertexBuffer>(positions, 4 * 4 * sizeof(float));

    m_VertexBufferLayout = std::make_unique<lada::render::VertexBufferLayout>();
    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(2);
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
    m_IndexBuffer = std::make_unique<lada::render::IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<lada::render::Shader>(workingDirectory + "/lada_sandbox/res/shaders/Basic.glsl");
    m_Shader->Bind();

    m_Texture = std::make_unique<lada::render::Texture>(workingDirectory + "/lada_sandbox/res/textures/stone.png");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
}

void DemoApp::BeforeRender() {
    // const glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
    const glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);
    constexpr glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    const glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f * m_R), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * view * model;
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    m_Shader->SetUniform4f("u_Color", m_R, 0.3f, 0.8f, 1.0f);
    m_Renderer.Clear();
}

void DemoApp::OnRender() {
    m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void DemoApp::OnImGuiRender(const float frameRate) {
    ImGui::Begin("Lada::Debug");
    ImGui::SliderFloat("Rotation", &m_R, 0.0f, 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / frameRate, frameRate);
    ImGui::End();
}

void DemoApp::AfterRender() {
    if (m_R > 1.0f) {
        m_R = 0.0f;
    }
    m_R += m_Increment;
}
