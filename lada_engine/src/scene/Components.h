#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <spdlog/fmt/bundled/format.h>

#include "assets/Asset.h"
#include "core/UUID.h"

namespace Lada {
    struct IdComponent {
        UUID ID = UUID();

        explicit IdComponent(const UUID &id)
            : ID(id) {
        }
    };

    struct NameComponent {
        std::string Name = "UNNAMED";

        NameComponent() = default;
        NameComponent(const NameComponent& other) = default;

        explicit NameComponent(const std::string& name)
            : Name(name) {}

        explicit operator std::string& () { return Name; }
        explicit operator const std::string& () const { return Name; }
    };

    struct FolderComponent {
        std::vector<std::string> Path;
        FolderComponent(): Path({}) {}
        explicit FolderComponent(const std::vector<std::string>& path): Path(path) {}
        explicit operator std::string ();
    };

    struct TransformComponent {
        glm::vec3 Translation = glm::vec3(0.0f);
        glm::quat Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

        TransformComponent() = default;

        TransformComponent(const glm::vec3 &translation, const glm::quat &rotation, const glm::vec3 &scale)
            : Translation(translation),
              Rotation(rotation),
              Scale(scale) {
        }

        glm::mat4 Transform() const;

        glm::mat4 NormalTransform() const;
    };

    enum class CameraType {
        Orthographic,
        Perspective
    };

    struct CameraComponent {
        CameraType Type = CameraType::Perspective;
        float FOVDegrees = 60.0f;
        float OrthoSize = 10.0f;
        bool AutoAspectRatio = true;
        float AspectRatio = 1.778f;

        float NearPlane = 0.1f;
        float FarPlane = 1000.0f;

        float ViewportX = 0.0f;
        float ViewportY = 0.0f;
        float ViewportWidth = 1.0f;
        float ViewportHeight = 1.0f;

        bool Primary = true;

        glm::vec3 ClearColor = glm::vec3(0.0f);
    };

    struct MeshComponent {
        AssetID MeshID;

        explicit MeshComponent(const AssetID &meshId)
            : MeshID(meshId) {
        }
    };
}
