#pragma once
#include "renderer/Mesh.h"

namespace Lada::Render {
    class ModelLoader {
    public:
        std::shared_ptr<Mesh> LoadModel(const std::string &filePath);
    };
}
