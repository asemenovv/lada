#pragma once
#include "ComponentArray.h"
#include "ECSUtils.h"

namespace Lada {
    class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent();

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        void AddComponent(Entity entity, T component);

        template<typename T>
        void RemoveComponent(Entity entity);

        template<typename T>
        T& GetComponent(Entity entity);

        void EntityDestroyed(Entity entity) const;
    private:
        std::unordered_map<const char*, ComponentType> m_ComponentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};
        ComponentType m_NextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray();
    };
}
