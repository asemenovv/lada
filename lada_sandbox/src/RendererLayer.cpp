#include "ldpch.h"
#include "RendererLayer.h"

#include "ContextVars.h"

void RendererLayer::OnAttach(Lada::App::LayerContext *context) {
    m_Renderer = std::make_shared<Lada::Render::Renderer>(Lada::App::Application::Get().GetWindow());

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

    m_Material = Lada::Render::MaterialBuilder(workingDirectory + "/lada_sandbox/res/shaders/Basic.glsl")
    .WithTexture("u_Texture", workingDirectory + "/lada_sandbox/res/textures/stone.png")
    .WithVector4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
    .Build();

    m_Square = Lada::Render::MeshBuilder(positions, 4 * 4 * sizeof(float))
    .PushToLayout<float>(2)
    .PushToLayout<float>(2)
    .FinalizeBuffer()
    .Indices(indices, 6)
    .WithMaterial(m_Material)
    .Build();

    m_Renderer->SubmitMesh(m_Square);
}

void RendererLayer::OnUpdate(Lada::App::LayerContext *context) {
    const auto rotation = context->GetF(SQUARE_ROTATION);
    const auto rotationIncrement = context->GetF(SQUARE_ROTATION_INCREMENT);
    if (*rotation > 1.0f) {
        context->SetF(SQUARE_ROTATION, 0.0f);
    }
    context->SetF(SQUARE_ROTATION, (*rotation) + (*rotationIncrement));
}

void RendererLayer::OnRender(Lada::App::LayerContext *context) {
    m_Renderer->BeginFrame();
    m_Renderer->Draw();
    m_Renderer->EndFrame();
}
