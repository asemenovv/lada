#pragma once

#include <sstream>

#include "Event.h"

namespace lada::event {
    class WindowResizeEvent final : public Event {
    public:
        WindowResizeEvent(int width, int height): m_Width(width), m_Height(height) {
        }

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        std::string ToString() const override {
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

        int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }
        EVENT_CLASS_TYPE(WindowClose);
    };

    class AppTickEvent final : public Event {
    public:
        AppTickEvent() = default;

        int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }
        EVENT_CLASS_TYPE(AppTick);
    };

    class AppUpdateEvent final : public Event {
    public:
        AppUpdateEvent() = default;
        int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        EVENT_CLASS_TYPE(AppUpdate);
    };

    class AppRenderEvent final : public Event {
    public:
        AppRenderEvent() = default;
        int GetCategoryFlags() const override { return static_cast<int>(EventCategory::EventCategoryApplication); }

        EVENT_CLASS_TYPE(AppRender);
    };
}
