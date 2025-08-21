#pragma once

#include "ECSUtils.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace Lada {
    class EcsCoordinator {
    public:
        EcsCoordinator();

        Entity CreateEntity() const;
        void DestroyEntity(Entity entity) const;

        template<typename T>
        void RegisterComponent() const;
        template<typename T>
        void AddComponent(Entity entity, T component);
        template<typename T>
        void RemoveComponent(Entity entity) const;
        template<typename T>
        T& GetComponent(Entity entity);
        template<typename T>
        ComponentType GetComponentType() const;

        template<typename T>
        std::shared_ptr<T> RegisterSystem();
        template<typename T>
        void SetSystemSignature(Signature signature) const;
    private:
        std::unique_ptr<ComponentManager> mComponentManager;
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<SystemManager> mSystemManager;
    };
}
