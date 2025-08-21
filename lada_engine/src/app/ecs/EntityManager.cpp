#include "EntityManager.h"

#include <cassert>

#include "app/Logger.h"

namespace Lada {
    EntityManager::EntityManager() {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            m_AvailableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity() {
        LD_CORE_ASSERT_WITH_ERROR(m_LivingEntityCount < MAX_ENTITIES, "Too many entities in existence.");

        const Entity id = m_AvailableEntities.front();
        m_AvailableEntities.pop();
        ++m_LivingEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(const Entity entity) {
        LD_CORE_ASSERT_WITH_ERROR(entity < MAX_ENTITIES, "Entity out of range.");

        m_Signatures[entity].reset();
        m_AvailableEntities.push(entity);
        --m_LivingEntityCount;
    }

    void EntityManager::SetSignature(const Entity entity, const Signature signature) {
        LD_CORE_ASSERT_WITH_ERROR(entity < MAX_ENTITIES, "Entity out of range.");

        m_Signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(const Entity entity) const {
        LD_CORE_ASSERT_WITH_ERROR(entity < MAX_ENTITIES, "Entity out of range.");

        return m_Signatures[entity];
    }
}
