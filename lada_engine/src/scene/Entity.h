#pragma once

#include "Scene.h"
#include "app/Logger.h"
#include "core/UUID.h"
#include <entt/entity/entity.hpp>

namespace Lada {
    using EntityID = UUID;

    class Entity {
    public:
        explicit Entity(entt::entity entity, Scene* scene);
        ~Entity() = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        template<typename... T>
        bool HasComponent() const;
    private:
        entt::entity m_Entity;
        Scene* m_Scene;
        EntityID m_ID;
    };

    template<typename T, typename ... Args>
    T& Entity::AddComponent(Args &&...args) {
        if (HasComponent()) {
            LD_CORE_WARN("Entity already has component!");
        }
        return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
    }

    template<typename ... T>
    bool Entity::HasComponent() const {
        return m_Scene->m_Registry.any_of<T...>(m_Entity);
    }
}
