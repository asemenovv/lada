#include "ldpch.h"
#include "RenderingLayer.h"

#include "ContextVars.h"

void RenderingLayer::OnAttach(Lada::App::LayerContext* context) {

}

void RenderingLayer::OnAttach(Lada::App::LayerContext* context) {
    std::string workingDirectory = Lada::workingDir();
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

    m_VertexArray = std::make_unique<Lada::Render::VertexArray>();
    m_VertexBuffer = std::make_unique<Lada::Render::VertexBuffer>(positions, 4 * 4 * sizeof(float));

    m_VertexBufferLayout = std::make_unique<Lada::Render::VertexBufferLayout>();
    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(2);
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
    m_IndexBuffer = std::make_unique<Lada::Render::IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Lada::Render::Shader>(workingDirectory + "/lada_sandbox/res/shaders/Basic.glsl");
    m_Shader->Bind();

    m_Texture = std::make_unique<Lada::Render::Texture>(workingDirectory + "/lada_sandbox/res/textures/stone.png");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);

    context->SetF(SQUARE_ROTATION, 0.0f);
    context->SetF(SQUARE_ROTATION_INCREMENT, 0.001f);
}

void RenderingLayer::OnDetach(Lada::App::LayerContext* context) {
    Layer::OnDetach(context);
}

void RenderingLayer::OnUpdate(Lada::App::LayerContext* context) {
    const auto rotation = context->GetF(SQUARE_ROTATION);
    const auto rotationIncrement = context->GetF(SQUARE_ROTATION_INCREMENT);
    // const glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
    const glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);
    constexpr glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    const glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f * (*rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * view * model;
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    m_Shader->SetUniform4f("u_Color", *rotation, 0.3f, 0.8f, 1.0f);
    m_Renderer.Clear();

    if (*rotation > 1.0f) {
        context->SetF(SQUARE_ROTATION, 0.0f);
    }
    context->SetF(SQUARE_ROTATION, (*rotation) + (*rotationIncrement));
}

void RenderingLayer::OnRender(Lada::App::LayerContext* context) {
    m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}


