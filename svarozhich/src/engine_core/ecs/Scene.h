#pragma once
#include <vector>

#include "Entity.h"

namespace Svch {
    class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        EntityID CreateEntity(const std::string& entity_name, const std::vector<std::string>& folderPath);

    private:
        std::vector<Entity> m_Entities;
    };
}
