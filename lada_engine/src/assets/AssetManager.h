#pragma once
#include "renderer/material/Shader.h"
#include "renderer/material/Texture.h"
#include "renderer/material/Material.h"
#include "app/Logger.h"

#include <yaml-cpp/yaml.h>
#include <stb_image.h>

namespace Lada {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class AssetManager {
    public:
        template<typename T>
        static std::shared_ptr<T> Load(const std::string &path);

        static std::string WorkingDir();
    private:
        template<typename T>
        static std::shared_ptr<T> LoadInternal(const std::string &path);

        static ShaderProgramSource ParseShader(const std::string &filepath);
    };

    template<typename T>
    std::shared_ptr<T> AssetManager::Load(const std::string &path) {
        static std::unordered_map<std::string, std::weak_ptr<IAsset> > cache;

        if (const auto it = cache.find(path); it != cache.end()) {
            if (const auto shared = it->second.lock()) {
                return std::static_pointer_cast<T>(shared);
            }
        }
        auto asset = LoadInternal<T>(path);
        cache[path] = asset;
        return asset;
    }

    template<>
    inline std::shared_ptr<Shader> AssetManager::LoadInternal<Shader>(const std::string &path) {
        LD_CORE_INFO("Loading shader: '{0}'", path);
        auto [vertexSource, fragmentSource] = ParseShader(WorkingDir() + path);
        return std::make_shared<Shader>(vertexSource, fragmentSource);
    }

    template<>
    inline std::shared_ptr<Texture> AssetManager::LoadInternal<Texture>(const std::string &path) {
        unsigned char *localBuffer = nullptr;
        int width, height, BPP;
        stbi_set_flip_vertically_on_load(1);
        const std::string absolutePath = WorkingDir() + path;
        localBuffer = stbi_load(absolutePath.c_str(), &width, &height, &BPP, 4);
        LD_CORE_INFO("Loading texture: '{0}' ({1}x{2})", path, width, height);
        auto texture = std::make_shared<Texture>(localBuffer, width, height, BPP);
        if (localBuffer) {
            stbi_image_free(localBuffer);
        }
        return texture;
    }

    template<>
    inline std::shared_ptr<Material> AssetManager::LoadInternal<Material>(const std::string &path) {
        LD_CORE_INFO("Loading material: '{0}'", path);
        YAML::Node root = YAML::LoadFile(WorkingDir() + path);
        const auto shaderUri = root["program"]["uri"].as<std::string>();
        const auto shader = Load<Shader>(shaderUri);
        auto material = std::make_shared<Material>(shader);
        const auto materialName = root["name"].as<std::string>();
        material->SetName(materialName);
        if (root["textures"].IsSequence()) {
            for (const auto& textureNode : root["textures"]) {
                const auto textureName = textureNode["name"].as<std::string>();
                const auto variable = textureNode["variable"].as<std::string>();
                const auto textureUri = textureNode["uri"].as<std::string>();
                auto texture = Load<Texture>(textureUri);
                texture->SetName(textureName);
                material->SetTexture(variable, texture);
            }
        }
        if (root["uniforms"].IsSequence()) {
            for (const auto& uniformNode : root["uniforms"]) {
                const auto uniformName = uniformNode["name"].as<std::string>();
                const auto variable = uniformNode["variable"].as<std::string>();
                if (uniformNode["type"].as<std::string>() == "COLOR") {
                    glm::vec4 value;
                    const auto val = uniformNode["value"];
                    value.r = val[0].as<float>();
                    value.g = val[1].as<float>();
                    value.b = val[2].as<float>();
                    value.a = val[3].as<float>();
                    material->SetVector4(variable, value);
                } else {
                    LD_CORE_ERROR("Unsupported uniform type in material.");
                }
            }
        }
        return material;
    }
}
