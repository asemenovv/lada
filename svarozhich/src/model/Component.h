#pragma once
#include "Math.h"

namespace Svch {
    enum class ComponentType {
        TRANSFORM,
        CAMERA,
        MESH,
        MATERIAL,
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT,
    };

    class Component {
    public:
        Component() = default;

        virtual ~Component() = default;

        [[nodiscard]] virtual ComponentType GetType() const { throw "Not implemented"; }
    };

    class TransformComponent final : public Component {
    public:
        TransformComponent() : Component(), m_Position({}), m_Rotation({}), m_Scale({1.0, 1.0, 1.0}) {
        }

        [[nodiscard]] ComponentType GetType() const override {
            return ComponentType::TRANSFORM;
        }

        void SetPosition(const Vector3f &position) {
            m_Position = position;
        }

        [[nodiscard]] const Vector3f &GetPosition() const { return m_Position; }

        void SetRotation(const Vector3f &rotation) {
            m_Rotation = rotation;
        }

        [[nodiscard]] const Vector3f &GetRotation() const { return m_Rotation; }

        void SetScale(const Vector3f &scale) {
            m_Scale = scale;
        }

        [[nodiscard]] const Vector3f &GetScale() const { return m_Scale; }

    private:
        Vector3f m_Position;
        Vector3f m_Rotation;
        Vector3f m_Scale;
    };

    enum class CameraProjectionMode {
        Orthographic = 0,
        Perspective = 1
    };

    class CameraComponent final : public Component {
    public:
        CameraComponent();
    private:
        bool m_Primary = true;
        CameraProjectionMode m_ProjectionMode = CameraProjectionMode::Perspective;
        float m_FOV = 45.0f;
        float m_Size = 1.0;
        float m_NearPlane = 0.01;
        float m_FarPlane = 1000.0;
    };
}
