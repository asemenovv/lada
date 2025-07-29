#include "ldpch.h"
#include "AssetManager.h"

#include <yaml-cpp/node/convert.h>

#include "renderer/material/Material.h"
#include "yaml-cpp/node/parse.h"

namespace Lada {
    template<typename T>
    std::shared_ptr<T> AssetManager::Load(const std::string& path) {

    }

    template<>
    std::shared_ptr<Material> AssetManager::LoadInternal<Material>(const std::string& path) {
        YAML::Node node = YAML::LoadFile(path);
    }
}
