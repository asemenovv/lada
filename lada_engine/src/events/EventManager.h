#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "IEventListener.h"
#include "EventBus.h"

namespace lada::event {
    class EventManager {
    public:
        template<typename T>
        void RegisterListener(IEventListener<T>* listener) {
            GetOrCreateBus<T>()->RegisterListener(listener);
        }

        template<typename T>
        void HandleEvent(const T& event) {
            auto it = m_Buses.find(std::type_index(typeid(T)));
            if (it != m_Buses.end()) {
                auto* typed = static_cast<TypedBus<T>*>(it->second.get());
                typed->bus.HandleEvent(event);
            }
        }
    private:
        struct IBus {
            virtual ~IBus() = default;
        };

        template<typename T>
        struct TypedBus final : IBus {
            EventBus<T> bus;
        };

        template<typename T>
        EventBus<T>* GetOrCreateBus() {
            const std::type_index key = std::type_index(typeid(T));
            auto it = m_Buses.find(key);
            if (it == m_Buses.end()) {
                auto typedBus = std::make_unique<TypedBus<T>>();
                auto* ref = &typedBus->bus;
                m_Buses[key] = std::move(typedBus);
                return ref;
            }
            return &static_cast<TypedBus<T>*>(m_Buses[key].get())->bus;
        }

        std::unordered_map<std::type_index, std::unique_ptr<IBus>> m_Buses;
    };
}
