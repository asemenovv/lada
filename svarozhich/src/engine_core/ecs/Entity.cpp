#include "Entity.h"

#include <utility>

#include "model/Math.h"

namespace Svch {
    Entity::Entity(const std::string &name)
        : Entity(NewId(), name) {
    }

    Entity::Entity(const unsigned int id, const std::string &name)
        : Entity(id, name, {}) {}

    Entity::Entity(const std::string &name, const std::vector<std::string> &folderPath)
        : Entity(NewId(), name, folderPath) {
    }

    Entity::Entity(const unsigned int id, std::string name, std::vector<std::string> folderPath)
        : m_ID(id), m_Name(std::move(name)), m_FolderPath(std::move(folderPath)) {
    }

    unsigned int Entity::NewId() {
        static std::size_t counter = 0;
        return ++counter;
    }
}
