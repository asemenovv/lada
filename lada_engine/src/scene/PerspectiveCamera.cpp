#include "PerspectiveCamera.h"

namespace Lada {
    PerspectiveCamera::PerspectiveCamera(const CameraComponent &cameraComponent,
        const TransformComponent &transformComponent, struct SwapChain::Extent extent): SceneCamera(cameraComponent, extent) {
        const float aspect = (cameraComponent.AutoAspectRatio) ? extent.AspectRatio() : cameraComponent.AspectRatio;
        m_ProjectionMatrix = glm::perspective(cameraComponent.FOVDegrees, aspect, cameraComponent.NearPlane, cameraComponent.FarPlane);
        const glm::mat4 rot = glm::mat4_cast(glm::conjugate(transformComponent.Rotation));
        m_ViewMatrix = rot;
        m_ViewMatrix[3] = rot * glm::vec4(-transformComponent.Translation, 1.0f);
    }
}
