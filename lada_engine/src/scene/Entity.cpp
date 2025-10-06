#include "Entity.h"

namespace Lada {
    Entity::Entity(const entt::entity entity, Scene* scene): m_Entity(entity), m_ID(UUID()), m_Scene(scene) {}
}