#include "ldpch.h"
#include "RendererLayer.h"

#include "ContextVars.h"
#include "renderer/model/ModelLoader.h"

void RendererLayer::OnAttach(Lada::App::LayerContext *context) {
    std::string workingDirectory = Lada::workingDir();
    LD_INFO("Working directory is {0}", workingDirectory);

    constexpr float positions[] = {
        -0.5f, -0.5f, 2.0, 0.0f, 0.0f,
        0.5f, -0.5f, 2.0, 1.0f, 0.0f,
        0.5f, 0.5f, 2.0, 1.0f, 1.0f,
        -0.5f, 0.5f, 2.0, 0.0f, 1.0f,
    };
    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<Lada::Render::Material> material = Lada::Render::MaterialBuilder(
                workingDirectory + "/lada_sandbox/res/shaders/Basic.glsl")
            .WithTexture("u_Texture", workingDirectory + "/lada_sandbox/res/textures/stone.png")
            .WithVector4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
            .Build();

    // Lada::Render::ModelLoader loader;
    // m_Square = loader.LoadModel(workingDirectory + "/assets/gltf_sample_models/2.0/BoxTextured/glTF/BoxTextured.gltf");
    // m_Square->SetMaterial(m_Material);

    std::shared_ptr<Lada::Render::Mesh> squareMesh = Lada::Render::MeshBuilder(positions, 4 * 5 * sizeof(float))
            .PushToLayout<float>(3)
            .PushToLayout<float>(2)
            .FinalizeBuffer()
            .Indices(indices, 6)
            .Build();

    m_Square = Lada::Render::ModelBuilder()
            .PushMesh(squareMesh, material)
            .DefaultTransformation()
            .Scale(15)
            .Build();
}

void RendererLayer::OnUpdate(Lada::App::LayerContext *context) {
    const auto rotation = context->GetF(SQUARE_ROTATION);
    const auto rotationIncrement = context->GetF(SQUARE_ROTATION_INCREMENT);
    if (*rotation > 1.0f) {
        context->SetF(SQUARE_ROTATION, 0.0f);
    }
    context->SetF(SQUARE_ROTATION, (*rotation) + (*rotationIncrement));
}

void RendererLayer::OnRender(Lada::App::LayerContext *context,
                             const std::shared_ptr<Lada::Render::Renderer> &renderer) {
    renderer->Submit(m_Square);
}
