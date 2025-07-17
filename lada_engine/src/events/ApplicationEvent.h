#pragma once

#include <sstream>

#include "Event.h"

namespace Lada::Event {
    class WindowResizeEvent final : public Event {
    public:
        WindowResizeEvent(const int width, const int height): m_Width(width), m_Height(height) {
        }

        [[nodiscard]] unsigned int GetWidth() const { return m_Width; }
        [[nodiscard]] unsigned int GetHeight() const { return m_Height; }

        [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)

    private:
        int m_Width, m_Height;
    };

    class WindowCloseEvent final : public Event {
    public:
        WindowCloseEvent() = default;

        [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }
        EVENT_CLASS_TYPE(WindowClose);
    };

    class AppTickEvent final : public Event {
    public:
        AppTickEvent() = default;

        [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }
        EVENT_CLASS_TYPE(AppTick);
    };

    class AppUpdateEvent final : public Event {
    public:
        AppUpdateEvent() = default;
        [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        EVENT_CLASS_TYPE(AppUpdate);
    };

    class AppRenderEvent final : public Event {
    public:
        AppRenderEvent() = default;
        [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        EVENT_CLASS_TYPE(AppRender);
    };
}
