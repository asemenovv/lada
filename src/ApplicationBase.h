#include <string>

struct GLFWwindow;

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
    virtual void Render(float frameRate);
    virtual void AfterRender();
    virtual void CleanUp();
};
