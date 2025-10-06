#pragma once
#include "Components.h"
#include "SceneCamera.h"

namespace Lada {
    class PerspectiveCamera final : public SceneCamera {
    public:
        PerspectiveCamera(const CameraComponent& cameraComponent, const TransformComponent& transformComponent,
            struct SwapChain::Extent extent);
    };
}
