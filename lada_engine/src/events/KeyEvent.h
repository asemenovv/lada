#pragma once

#include <sstream>

#include "Event.h"
#include "util/KeyCodes.h"

namespace lada::event {
    class KeyEvent : public Event {
    public:
        [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

        [[nodiscard]] int GetCategoryFlags() const override {
            return static_cast<int>(EventCategory::EventCategoryKeyboard)
            | static_cast<int>(EventCategory::EventCategoryInput);
        };

    protected:
        explicit KeyEvent(const int keycode) : m_KeyCode(keycode) {
        }

        int m_KeyCode;
    };

    class KeyPressedEvent final : public KeyEvent {
    public:
        KeyPressedEvent(const int keycode, const int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {
        }

        [[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (with " << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent final : public KeyEvent {
    public:
        explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent final : public KeyEvent {
    public:
        explicit KeyTypedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}
