#include "ldpch.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "AssetManager.h"


namespace Lada {
    ShaderProgramSource AssetManager::ParseShader(const std::string& filepath) {
        std::ifstream stream(filepath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        auto type = ShaderType::NONE;
        while (std::getline(stream, line)) {
            if (line.find("//shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            } else {
                ss[static_cast<int>(type)] << line << std::endl;
            }
        }
        stream.close();
        return { ss[0].str(), ss[1].str() };
    }

    AssetID AssetManager::Register(const AssetType type, const std::string &path) {
        auto id = UUID();
        switch (type) {
            case AssetType::Mesh:
                m_Assets[id] = LoadInternal<Mesh>(path, id);
                break;
            default:
                LD_CORE_CRITICAL("Unsupported Asset Type!");
                std::abort();
        }
        return id;
    }

    template<typename T>
    T* AssetManager::Get(AssetID &id) {
        return m_Assets[id].get();
    }

    std::string AssetManager::WorkingDir() {
        const std::filesystem::path currentPath = std::filesystem::current_path()
            .parent_path()
            .parent_path();
        auto directory = currentPath.string() + '/';
        static bool isDirectoryLogged = false;
        if (isDirectoryLogged == false) {
            isDirectoryLogged = true;
            LD_CORE_INFO("Working directory is {0}", directory);
        }
        return directory;
    }
}
