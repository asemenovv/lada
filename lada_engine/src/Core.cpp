#include "ldpch.h"
#include "Core.h"

namespace Lada {
    std::string workingDir() {
        const std::filesystem::path currentPath = std::filesystem::current_path()
            .parent_path()
            .parent_path();
        std::string currentDirectory = currentPath.string();
        return currentDirectory;
    }
}
