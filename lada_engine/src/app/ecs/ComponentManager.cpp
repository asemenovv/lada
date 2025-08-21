#include "ComponentManager.h"

#include <ranges>

#include "app/Logger.h"

namespace Lada {
    template <typename T>
    void ComponentManager::RegisterComponent() {
        const char* typeName = typeid(T).name();

        LD_CORE_ASSERT_WITH_ERROR(!m_ComponentTypes.contains(typeName), "Registering component type more than once.");

        // Add this component type to the component type map
        m_ComponentTypes.insert({typeName, m_NextComponentType});
        m_ComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        ++m_NextComponentType;
    }

    template <typename T>
    ComponentType ComponentManager::GetComponentType() {
        const char* typeName = typeid(T).name();

        LD_CORE_ASSERT_WITH_ERROR(m_ComponentTypes.contains(typeName), "Component not registered before use.");

        return m_ComponentTypes[typeName];
    }

    template <typename T>
    void ComponentManager::AddComponent(Entity entity, T component) {
        getComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    void ComponentManager::RemoveComponent(Entity entity) {
        getComponentArray<T>()->RemoveData(entity);
    }

    template <typename T>
    T& ComponentManager::GetComponent(Entity entity) {
        return getComponentArray<T>()->GetData(entity);
    }

    void ComponentManager::EntityDestroyed(const Entity entity) const {
        for (const auto& component : m_ComponentArrays | std::views::values) {
            component->EntityDestroyed(entity);
        }
    }

    template <typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray() {
        const char* typeName = typeid(T).name();
        LD_CORE_ASSERT_WITH_ERROR(m_ComponentTypes.contains(typeName), "Component not registered before use.");
        return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
    }
}
