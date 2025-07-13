#pragma once

#include <string>

struct GLFWwindow;

namespace lada::app {
    class Application {
        GLFWwindow* m_Window;
        int m_Width, m_Height;
        std::string m_Title;
    public:
        virtual ~Application() = default;
        Application(const std::string& title, int width, int height);
        void Run();
    protected:
        virtual void Init();
        virtual void BeforeRender();
        virtual void OnRender();
        virtual void OnImGuiRender(float frameRate);
        virtual void AfterRender();
        virtual void CleanUp();
    };
}
