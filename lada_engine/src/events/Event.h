#pragma once
#include <string>

#include "Core.h"
#include "spdlog/fmt/bundled/base.h"

namespace Lada::Event {
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
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

#define REGISTER_HANDLER(e, x) RegisterHandler<e>([this](const e& event) x)
#define EVENT_CLASS_TYPE(type) virtual EventType GetEventType() const override { return EventType::type; }\
virtual const char* GetName() const override { return #type; }

    class Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const  = 0;
        [[nodiscard]] virtual int GetCategoryFlags() const = 0;
        [[nodiscard]] virtual std::string ToString() const { return GetName(); }

        [[nodiscard]] bool IsInCategory(EventCategory category) const {
            return GetCategoryFlags() & static_cast<int>(category);
        }
        [[nodiscard]] bool IsHandled() const { return m_Handled; }
        void Handled() { m_Handled = true; }
    protected:
        bool m_Handled = false;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}
