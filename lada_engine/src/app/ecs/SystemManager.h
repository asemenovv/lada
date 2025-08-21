#pragma once

#include "ECSUtils.h"
#include "System.h"

namespace Lada {
    class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSignature(Signature signature);

        void EntityDestroyed(Entity entity);

        void EntitySignatureChanged(Entity entity, Signature entitySignature);
    private:
        std::unordered_map<const char*, Signature> m_Signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};
    };
}
