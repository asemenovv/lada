#pragma once

#include <vector>

#include "IEventListener.h"

namespace lada::event {
    class EventBus {
    public:
        template<typename EVENT>
        void RegisterListener(IEventListener<EVENT>* listener) {
            m_Listeners.push_back(listener);
        }

        template<typename EVENT>
        void UnregisterListener(IEventListener<EVENT>* listener) {
            auto it = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
            if (it != m_Listeners.end()) {
                m_Listeners.erase(it);
            }
        }

        template<typename EVENT>
        bool HandleEvent(EVENT* event) {
            bool isHandled = false;
            for (IEventListener<EVENT>* listener : m_Listeners) {
                if (listener->GetStaticType() != event->GetStaticType()) {
                    continue;
                }
                if (listener->OnEvent(event)) {
                    isHandled = true;
                }
            }
            return isHandled;
        }

    private:
        std::vector<IEventListener*> m_Listeners;
    };
}
