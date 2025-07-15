#pragma once
#include <string>

#include "Core.h"

namespace lada::event {
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    class Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual std::string GetName() const  { return GetEventType(); };
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) const {
            return GetCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };

    class EventDispatcher {

    };
}
