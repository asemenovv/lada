#pragma once

#include "events/EventManager.h"
#include "renderer/GraphicsApiFactory.h"

namespace Lada {
    struct WindowSize {
        const int width;
        int height;
    };

    class Window {
    public:
        Window(int width, int height, std::shared_ptr<EventManager> &eventManager);

        virtual ~Window() = default;

        virtual void OnUpdate() const = 0;

        virtual void SetVSync(bool enabled) = 0;

        virtual void Close() const = 0;

        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }
        [[nodiscard]] virtual WindowSize GetPixelsSize() = 0;

        virtual void *GetNativeWindow() = 0;

        static std::shared_ptr<Window> Create(std::string title, int width, int height,
                                              std::shared_ptr<EventManager> &eventManager, GraphicAPI api);

    protected:
        int m_Width, m_Height;
        std::shared_ptr<EventManager> m_EventManager;
    };
}
