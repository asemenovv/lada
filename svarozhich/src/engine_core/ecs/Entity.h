#pragma once

typedef unsigned int EntityID;

namespace Svch {
    class Entity {
    public:
        explicit Entity(const std::string& name);

        explicit Entity(EntityID id, const std::string& name);

        explicit Entity(const std::string &name, const std::vector<std::string> &folderPath);

        explicit Entity(EntityID id, std::string  name, std::vector<std::string> folderPath);

        [[nodiscard]] EntityID GetID() const {
            return m_ID;
        }

        [[nodiscard]] std::string GetName() const {
            return m_Name;
        }

        [[nodiscard]] std::vector<std::string> GetFolderPath() const {
            return m_FolderPath;
        }

        static unsigned int NewId();
    private:
        EntityID m_ID;
        std::string m_Name;
        std::vector<std::string> m_FolderPath;
    };
}
