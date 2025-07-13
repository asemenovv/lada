#include <string>

struct GLFWwindow;

namespace lada::app {
    class ApplicationBase {
    private:
        GLFWwindow* m_Window;
        unsigned int m_Width, m_Height;
        std::string m_Title;
    public:
        ApplicationBase(const std::string& title, unsigned int width, unsigned int height);
        ~ApplicationBase();
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
