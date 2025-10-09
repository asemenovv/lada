#include "SceneRenderer.h"

#include "app/Logger.h"
#include "assets/AssetManager.h"

namespace Lada {
    SceneRenderer::SceneRenderer(Scene *scene, Render::Renderer* renderer, AssetManager* assetManager)
        : m_Scene(scene), m_Renderer(renderer), m_AssetManager(assetManager) {
    }

    void SceneRenderer::DrawScene() {
        auto meshes = m_Scene->GetAllEntitiesWith<TransformComponent, MeshComponent>();
        m_Renderer->BeginFrame();
        for (auto [ent, transform, mesh] : meshes.each()) {
            auto meshSource = m_AssetManager->Get<Mesh>(mesh.MeshID);
            m_Renderer->Submit(meshSource);
            // LD_CORE_DEBUG("Drawing mesh {}", ent);
        }
        m_Renderer->EndFrame();
    }
}
