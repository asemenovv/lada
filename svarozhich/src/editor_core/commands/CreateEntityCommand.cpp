#include "CreateEntityCommand.h"

namespace Svch {
    CreateEntityCommand::CreateEntityCommand(Scene *scene, EventBus *eventBus, const std::string &entityName,
        const std::vector<std::string> &folderPath) : m_Scene(scene), m_EventBus(eventBus),
        m_EntityID(0), m_EntityName(entityName), m_FolderPath(folderPath) {
    }

    void CreateEntityCommand::Redo() {
        m_EntityID = m_Scene->CreateEntity(m_EntityName, m_FolderPath);
    }

    void CreateEntityCommand::Undo() {
    }

    QString CreateEntityCommand::Text() {
        return QString::number(m_EntityID);
    }
}
