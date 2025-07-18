#pragma once

#include <sstream>

#include "Event.h"
#include "util/MouseCodes.h"

namespace Lada::Event {
    class MouseMovedEvent final : public Event {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_MouseX(x), m_MouseY(y) {
        }

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        [[nodiscard]] int GetCategoryFlags() const override {
            return static_cast<int>(EventCategory::EventCategoryMouse)
                   | static_cast<int>(EventCategory::EventCategoryInput);
        }

        EVENT_CLASS_TYPE(MouseMoved)

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent final : public Event {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {
        }

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        [[nodiscard]] int GetCategoryFlags() const override {
            return static_cast<int>(EventCategory::EventCategoryMouse)
                   | static_cast<int>(EventCategory::EventCategoryInput);
        }

        EVENT_CLASS_TYPE(MouseScrolled)

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        [[nodiscard]] int GetCategoryFlags() const override {
            return static_cast<int>(EventCategory::EventCategoryMouse)
                   | static_cast<int>(EventCategory::EventCategoryInput);
        }

    protected:
        explicit MouseButtonEvent(const MouseCode button)
            : m_Button(button) {
        }

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {
        }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {
        }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
