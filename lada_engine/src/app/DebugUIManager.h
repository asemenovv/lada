#pragma once

#include "Window.h"
// #include "Application.h"

namespace lada::app {
    class DebugUIManager {
    friend class Application;
    public:
        explicit DebugUIManager(const Window* window);
        ~DebugUIManager();

        float FrameRate();

        void Slider(const std::string &label, float* value, float min, float max);
        void Text(const char* fmt, ...);
    private:
        void Begin() const;
        void End() const;
        void BeforeRender();
        void AfterRender();
    };
}
