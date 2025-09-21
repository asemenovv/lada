#pragma once

#include "ICommand.h"
#include "engine_core/ecs/Entity.h"
#include "engine_core/ecs/Scene.h"
#include "engine_core/events/EventBus.h"

namespace Svch {
    class CreateEntityCommand final : public ICommand {
    public:
        CreateEntityCommand(Scene *scene, EventBus *eventBus, const std::string &entityName,
            const std::vector<std::string> &folderPath = {});
        ~CreateEntityCommand() override = default;

        void Redo() override;

        void Undo() override;

        QString Text() override;

    private:
        Scene *m_Scene;
        EventBus *m_EventBus;
        EntityID m_EntityID;
        std::string m_EntityName;
        std::vector<std::string> m_FolderPath;
    };
}
