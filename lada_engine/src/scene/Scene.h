#pragma once

#include <entt/entt.hpp>

#include "SceneCamera.h"
#include "renderer/GraphicsContext.h"

namespace Lada {
    class Entity;

    class Scene {
        friend class Entity;

    public:
        explicit Scene(GraphicsContext *graphicalContext);

        ~Scene() = default;

        Entity CreateEntity();

        std::unique_ptr<SceneCamera> PrimaryCamera();

        template<typename... Components>
        auto GetAllEntitiesWith() {
            return m_Registry.view<Components...>();
        }

    private:
        entt::registry m_Registry;
        GraphicsContext *m_GraphicalContext;
    };
}
