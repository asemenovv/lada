#pragma once

#include "Event.h"

namespace lada::event {
    template<typename T>
    class IEventListener {
    friend class EventBus;
    public:
        virtual ~IEventListener() = default;
        virtual bool OnEvent(const T& e) = 0;
    private:
        EventType GetStaticType() {
            return static_cast<EventType>(T::GetStaticType());
        }
    };

    // class WindowCloser final : public IEventListener<WindowCloseEvent> {
    // public:
    //     bool onEvent(const WindowCloseEvent &e) override {
    //         std::cout << "Window closed" << std::endl;
    //         return true;
    //     }
    // };
}
