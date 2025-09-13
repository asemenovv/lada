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

        [[nodiscard]] virtual ComponentType GetType() const;
    };

    class TransformComponent final : public Component {
    public:
        TransformComponent() : m_Position({}), m_Rotation({}), m_Scale({}) {
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
}
