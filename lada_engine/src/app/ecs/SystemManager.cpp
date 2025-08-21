#include "SystemManager.h"

#include <ranges>

#include "app/Logger.h"

namespace Lada {
    template <typename T>
    std::shared_ptr<T> SystemManager::RegisterSystem() {
        const char* typeName = typeid(T).name();

        LD_CORE_ASSERT_WITH_ERROR(!m_Systems.contains(typeName), "Registering system more than once.");

        auto system = std::make_shared<T>();
        m_Systems.insert({typeName, system});
        return system;
    }

    template <typename T>
    void SystemManager::SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();

        LD_CORE_ASSERT_WITH_ERROR(m_Systems.contains(typeName), "System used before registered.");

        // Set the signature for this system
        m_Signatures.insert({typeName, signature});
    }

    void SystemManager::EntityDestroyed(const Entity entity) {
        for (const auto& system : m_Systems | std::views::values) {
            system->m_Entities.erase(entity);
        }
    }

    void SystemManager::EntitySignatureChanged(const Entity entity, const Signature entitySignature) {
        for (const auto& [type, system] : m_Systems) {
            auto const& systemSignature = m_Signatures[type];

            if ((entitySignature & systemSignature) == systemSignature) {
                // Entity signature matches system signature - insert into set
                system->m_Entities.insert(entity);
            } else {
                // Entity signature does not match system signature - erase from set
                system->m_Entities.erase(entity);
            }
        }
    }
}
