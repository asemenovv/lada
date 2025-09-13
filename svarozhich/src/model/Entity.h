#pragma once

namespace Svch {
    class Entity {
    public:
        explicit Entity(const std::string& name);

        explicit Entity(unsigned int id, const std::string& name);

        explicit Entity(const std::string &name, const std::vector<std::string> &folderPath);

        explicit Entity(unsigned int id, std::string  name, std::vector<std::string> folderPath);

        [[nodiscard]] unsigned int GetID() const {
            return m_EntityID;
        }

        [[nodiscard]] std::string GetName() const {
            return m_Name;
        }

        [[nodiscard]] std::vector<std::string> GetFolderPath() const {
            return m_FolderPath;
        }

        static unsigned int NewId();
    private:
        unsigned int m_EntityID;
        std::string m_Name;
        std::vector<std::string> m_FolderPath;
    };
}
