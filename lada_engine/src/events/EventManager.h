#pragma once

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "events/Event.h"

namespace Lada {
    class EventManager {
    public:
        using GlobalEventHandler = std::function<bool(Event&)>;

        template<typename T>
        void RegisterHandler(std::function<bool(T&)> handler) {
            auto& handlers = GetHandlerList<T>();
            handlers.handlers.push_back(std::move(handler));
        }

        void RegisterGlobalHandler(GlobalEventHandler handler) {
            m_GlobalHandlers.emplace_back(std::move(handler));
        }

        template<typename T>
        bool HandleEvent(T& event) {
            const auto it = m_Handlers.find(std::type_index(typeid(T)));
            bool isHandled = false;
            if (it != m_Handlers.end()) {
                auto& rawList = it->second;
                auto& typedList = *static_cast<HandlerList<T>*>(rawList.get());
                for (auto& handler : typedList.handlers) {
                    if (handler(event)) {
                        isHandled = true;
                    }
                }
            }
            for (auto& handler : m_GlobalHandlers) {
                if (handler(event)) {
                    isHandled = true;
                }
            }
            return isHandled;
        }
    private:
        struct IHandlerList {
            virtual ~IHandlerList() = default;
        };

        template<typename T>
        struct HandlerList final : IHandlerList {
            std::vector<std::function<bool(T&)>> handlers;
        };

        template<typename T>
        HandlerList<T>& GetHandlerList() {
            const std::type_index key = std::type_index(typeid(T));
            const auto it = m_Handlers.find(key);
            if (it == m_Handlers.end()) {
                auto list = std::make_unique<HandlerList<T>>();
                auto* ref = list.get();
                m_Handlers[key] = std::move(list);
                return *ref;
            }
            return *static_cast<HandlerList<T>*>(m_Handlers[key].get());
        }

        std::unordered_map<std::type_index, std::unique_ptr<IHandlerList>> m_Handlers;
        std::vector<GlobalEventHandler> m_GlobalHandlers;
    };
}
