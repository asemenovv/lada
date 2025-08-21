#pragma once
#include "ECSUtils.h"

namespace Lada {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray final : public IComponentArray {
    public:
        void InsertData(Entity entity, T component);
        void RemoveData(Entity entity);
        T& GetData(Entity entity);
        void EntityDestroyed(Entity entity) override;
    private:
        std::array<T, MAX_ENTITIES> m_ComponentArray;
        std::unordered_map<Entity, size_t> m_EntityToIndexMap;
        std::unordered_map<size_t, Entity> m_IndexToEntityMap;
        size_t m_Size = 0;
    };
}
