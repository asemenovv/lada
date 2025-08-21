#pragma once
#include <queue>

#include "ECSUtils.h"

namespace Lada {
    class EntityManager {
    public:
        EntityManager();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity) const;
    private:
        std::queue<Entity> m_AvailableEntities{};
        std::array<Signature, MAX_ENTITIES> m_Signatures{};
        uint32_t m_LivingEntityCount{};
    };
}
