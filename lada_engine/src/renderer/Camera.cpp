#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lada::Render {
    Camera::Camera(const float fovGrad, const float aspect, const float near, const float far,
                   const glm::vec3 &position, const glm::vec3 &viewDirection,
                   const glm::vec3 &upDirection): m_FovGrad(fovGrad), m_Aspect(aspect),
                                                  m_Near(near), m_Far(far),
                                                  m_Position(position),
                                                  m_ViewDirection(viewDirection), m_UpDirection(upDirection) {
        UpdateMatrices();
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return m_ProjectionMatrix;
    }

    glm::mat4 Camera::GetViewProjectionMatrix() const {
        return m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::UpdateMatrices() {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FovGrad), m_Aspect, m_Near, m_Far);
        m_ViewMatrix = glm::lookAt(m_Position, m_ViewDirection, m_UpDirection);
    }

    CameraBuilder &CameraBuilder::Position(const glm::vec3 &position) {
        m_Position = position;
        return *this;
    }

    CameraBuilder &CameraBuilder::ViewDirection(const glm::vec3 &direction) {
        m_ViewDirection = direction;
        return *this;
    }

    CameraBuilder &CameraBuilder::UpDirection(const glm::vec3 &up) {
        m_UpDirection = up;
        return *this;
    }

    CameraBuilder &CameraBuilder::Screen(const float fovGrad, const float aspect, const float near, const float far) {
        m_FovGrad = fovGrad;
        m_Aspect = aspect;
        m_Near = near;
        m_Far = far;
        return *this;
    }

    std::shared_ptr<Camera> CameraBuilder::Build() const {
        return std::make_shared<Camera>(m_FovGrad, m_Aspect, m_Near, m_Far, m_Position, m_ViewDirection, m_UpDirection);
    }
}
