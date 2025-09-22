#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace Lada::Render {
    struct Viewport {
        float X = 0.0f;
        float Y = 0.0f;
        float Width = 1.0f;
        float Height = 1.0f;
        float MinDepth = 0.0f;
        float MaxDepth = 1.0f;
    };

    struct Scissor {
        float OffsetX = 0.0f;
        float OffsetY = 0.0f;
        float Width = 1.0f;
        float Height = 1.0f;
    };

    class Camera {
    public:
        Camera(float fovGrad, float aspect, float near, float far, const glm::vec3 &position,
               const glm::vec3 &viewDirection, const glm::vec3 &upDirection);

        glm::mat4 GetViewMatrix() const;

        glm::mat4 GetProjectionMatrix() const;

        glm::mat4 GetViewProjectionMatrix() const;

        Viewport GetViewport() const { return m_Viewport; }

        Scissor GetScissor() const { return m_Scissor; }
    private:
        float m_FovGrad;
        float m_Aspect;
        float m_Near;
        float m_Far;

        glm::vec3 m_Position;
        glm::vec3 m_ViewDirection;
        glm::vec3 m_UpDirection;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        Viewport m_Viewport = {};
        Scissor m_Scissor = {};

        void UpdateMatrices();
    };

    class CameraBuilder {
    public:
        CameraBuilder &Position(const glm::vec3 &position);

        CameraBuilder &ViewDirection(const glm::vec3 &direction);

        CameraBuilder &UpDirection(const glm::vec3 &up);

        CameraBuilder &Screen(const float fovGrad, const float aspect, const float near, const float far);

        std::shared_ptr<Camera> Build() const;

    private:
        glm::vec3 m_Position;
        glm::vec3 m_ViewDirection;
        glm::vec3 m_UpDirection;
        float m_FovGrad;
        float m_Aspect;
        float m_Near;
        float m_Far;
    };
}
