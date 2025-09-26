#include "Scene.h"

namespace Lada {
    FolderComponent::operator std::string&() {
        std::string path = fmt::format("{}", fmt::join(Path, ", "));
        return path;
    }
}
