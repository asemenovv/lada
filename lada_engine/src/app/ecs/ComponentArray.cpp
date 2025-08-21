#include "ComponentArray.h"

#include "app/Logger.h"

namespace Lada {
    template <typename T>
    void ComponentArray<T>::InsertData(const Entity entity, T component) {
        LD_CORE_ASSERT_WITH_ERROR(!m_EntityToIndexMap.contains(entity), "Component added to same entity more than once.");

        size_t newIndex = m_Size;
        m_EntityToIndexMap[entity] = newIndex;
        m_IndexToEntityMap[newIndex] = entity;
        m_ComponentArray[newIndex] = component;
        ++m_Size;
    }

    template <typename T>
    void ComponentArray<T>::RemoveData(const Entity entity) {
        LD_CORE_ASSERT_WITH_ERROR(m_EntityToIndexMap.contains(entity), "Removing non-existent component.");

        size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
        size_t indexOfLastElement = m_Size - 1;
        m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
        m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_EntityToIndexMap.erase(entity);
        m_IndexToEntityMap.erase(indexOfLastElement);

        --m_Size;
    }

    template <typename T>
    T& ComponentArray<T>::GetData(const Entity entity) {
        LD_CORE_ASSERT_WITH_ERROR(m_EntityToIndexMap.contains(entity), "Retrieving non-existent component.");

        return m_ComponentArray[m_EntityToIndexMap[entity]];
    }

    template <typename T>
    void ComponentArray<T>::EntityDestroyed(const Entity entity) {
        if (m_EntityToIndexMap.contains(entity)) {
            RemoveData(entity);
        }
    }
}
