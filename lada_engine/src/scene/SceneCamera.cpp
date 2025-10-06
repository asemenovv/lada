#include "SceneCamera.h"

namespace Lada {
    SceneCamera::SceneCamera(const CameraComponent &cameraComponent, const struct SwapChain::Extent& swapChainExtent)
        : m_ViewMatrix(glm::mat4(1)), m_ProjectionMatrix(glm::mat4(1)) {
        m_Viewport = {
            .X = cameraComponent.ViewportX * static_cast<float>(swapChainExtent.width),
            .Y = cameraComponent.ViewportY * static_cast<float>(swapChainExtent.height),
            .Width = cameraComponent.ViewportWidth * static_cast<float>(swapChainExtent.width),
            .Height = cameraComponent.ViewportHeight * static_cast<float>(swapChainExtent.height),
            .MinDepth = cameraComponent.NearPlane,
            .MaxDepth = cameraComponent.FarPlane
        };
    }
}
