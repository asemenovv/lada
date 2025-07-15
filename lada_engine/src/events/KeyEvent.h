#pragma once

#include <string>
#include <sstream>

#include "Event.h"

namespace lada::event {
    class KeyEvent : public Event {
    public:
        int GetKeyCode() const { return m_KeyCode; }

        int GetCategoryFlags() const override {
            return EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput;
        }

    protected:
        explicit KeyEvent(const int keycode) : m_KeyCode(keycode) {
        }

        int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(const int keycode, const int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {
        }

        int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (with " << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EventType GetEventType() const override { return EventType::KeyPressed; }

    private:
        int m_RepeatCount;
    };
}
