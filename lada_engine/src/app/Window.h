#pragma once

#include "events/EventManager.h"

namespace Lada {
    struct WindowSize {
        const int width;
        int height;
    };

    enum class GraphicAPI;

    class Window {
    public:
        Window(int width, int height, EventManager& eventManager);

        virtual ~Window() = default;

        virtual void OnUpdate() const = 0;

        virtual void SetVSync(bool enabled) = 0;

        virtual void Close() const = 0;

        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }
        [[nodiscard]] virtual WindowSize GetPixelsSize() = 0;

        virtual void *GetNativeWindow() = 0;

        static std::unique_ptr<Window> Create(std::string title, int width, int height,
                                              EventManager& eventManager, GraphicAPI api);

    protected:
        int m_Width, m_Height;
        EventManager& m_EventManager;
    };
}
