#pragma once
#include "renderer/DeprecatedMesh.h"

namespace Lada::Render {
    class ModelLoader {
    public:
        std::shared_ptr<DeprecatedMesh> LoadModel(const std::string &filePath);
    };
}
