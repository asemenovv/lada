#pragma once

#include <vector>

#include "IEventListener.h"

namespace lada::event {
    template<typename T>
    class EventBus {
    public:
        void RegisterListener(IEventListener<T>* listener) {
            m_Listeners.push_back(listener);
        }

        void UnregisterListener(IEventListener<T>* listener) {
            auto it = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
            if (it != m_Listeners.end()) {
                m_Listeners.erase(it);
            }
        }

        bool HandleEvent(const T& event) {
            for (auto* listener : m_Listeners) {
                if (listener->OnEvent(event)) {
                    return true;
                }
            }
            return false;
        }

    private:
        std::vector<IEventListener<T>*> m_Listeners;
    };
}
