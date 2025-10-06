#include "SceneRenderer.h"

#include "app/Logger.h"

namespace Lada {
    SceneRenderer::SceneRenderer(Scene *scene, Render::Renderer* renderer): m_Scene(scene), m_Renderer(renderer) {
    }

    void SceneRenderer::DrawScene() {
        auto meshes = m_Scene->GetAllEntitiesWith<TransformComponent, MeshComponent>();
        m_Renderer->BeginFrame();
        m_Renderer->Submit(nullptr);
        for (auto [ent, transform, mesh] : meshes.each()) {
            // LD_CORE_DEBUG("Drawing mesh {}", ent);
        }
        m_Renderer->EndFrame();
    }
}
