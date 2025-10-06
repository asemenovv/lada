#include "Components.h"

#include "glm/gtc/matrix_inverse.inl"
#include "spdlog/fmt/bundled/ranges.h"


namespace Lada {
    FolderComponent::operator std::string() {
        return fmt::format("{}", fmt::join(Path, ", "));
    }

    glm::mat4 TransformComponent::Transform() const {
        const glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);
        const glm::mat4 rotation = glm::toMat4(Rotation);
        const glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
        return translation * rotation * scale;
    }

    glm::mat4 TransformComponent::NormalTransform() const {
        const glm::mat3 result = glm::inverseTranspose(glm::mat3(Transform()));
        return glm::mat4(result);
    }
}
