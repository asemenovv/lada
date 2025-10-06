#pragma once

#include <glm/glm.hpp>

#include "Components.h"
#include "renderer/Camera.h"
#include "renderer/SwapChain.h"

namespace Lada {
    class SceneCamera {
    public:
        SceneCamera(const CameraComponent& cameraComponent, const struct SwapChain::Extent& swapChainExtent);
        virtual ~SceneCamera() = default;

        [[nodiscard]] glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

        [[nodiscard]] glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

        [[nodiscard]] Render::Viewport GetViewport() const { return m_Viewport; }
    protected:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        Render::Viewport m_Viewport;
    };
}
