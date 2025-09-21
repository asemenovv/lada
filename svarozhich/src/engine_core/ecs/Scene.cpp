#include "Scene.h"

namespace Svch {
    EntityID Scene::CreateEntity(const std::string &entity_name, const std::vector<std::string> &folderPath) {
        static EntityID currentId = 0;
        currentId++;
        return currentId;
    }
} // Svch