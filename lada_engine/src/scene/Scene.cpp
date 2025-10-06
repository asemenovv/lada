#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "PerspectiveCamera.h"

namespace Lada {
    Scene::Scene(GraphicsContext *graphicalContext): m_GraphicalContext(graphicalContext) {
    }

    Entity Scene::CreateEntity() {
        entt::entity entity = m_Registry.create();
        return Entity(entity, this);
    }

    std::unique_ptr<SceneCamera> Scene::PrimaryCamera() {
        auto screenExtent = m_GraphicalContext->GetSwapChain()->Extent();
        const CameraComponent* primaryCamera = nullptr;
        const TransformComponent* cameraTransform = nullptr;
        const auto camerasView = m_Registry.view<CameraComponent, TransformComponent>();
        for (auto [entity, camera, transform] : camerasView.each()) {
            if (camera.Primary) {
                primaryCamera = &camera;
                cameraTransform = &transform;
            }
        }
        if (primaryCamera == nullptr || cameraTransform == nullptr) {
            LD_CORE_CRITICAL("Scene does not have primary camera");
            std::abort();
        }
        if (primaryCamera->Type == CameraType::Perspective) {
            return std::make_unique<PerspectiveCamera>(*primaryCamera, *cameraTransform, screenExtent);
        } else if (primaryCamera->Type == CameraType::Orthographic) {
            return nullptr;
        }
        return nullptr;
    }
}
