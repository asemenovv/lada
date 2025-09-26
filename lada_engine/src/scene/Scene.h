

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "core/UUID.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/fmt/bundled/ranges.h"

namespace Lada {
    class Scene {
    public:
    private:
    };

    struct IdComponent {
        UUID ID = UUID();
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
        explicit operator std::string& ();
    };

    struct TransformComponent {
        glm::vec3 Translation = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::quat Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
    };
}
