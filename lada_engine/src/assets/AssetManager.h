#pragma once

namespace Lada {
    class AssetManager {
    public:
        template<typename T>
        static std::shared_ptr<T> Load(const std::string& path);
    private:
        template<typename T>
        static std::shared_ptr<T> LoadInternal(const std::string& path);
    };
}
