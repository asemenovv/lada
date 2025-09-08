#include "ldpch.h"
#include "OpenGLContext.h"

#include "app/GlCall.h"
#include "app/Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../vulkan/device/VulkanInstance.h"

namespace Lada {
    OpenGLContext::OpenGLContext(Window& window): m_Window(window) {
        // const auto instance = new VulkanInstance(true);
        // delete instance;
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_Window.GetNativeWindow()));
        if (const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !status) {
            LD_CORE_CRITICAL("Failed to initialize Glad!");
        }

        LD_CORE_INFO("OpenGL Info:");
        GL_CALL(const char* glVendor = (const char*)glGetString(GL_VENDOR));
        GL_CALL(const char* glRenderer = (const char*)glGetString(GL_RENDERER));
        GL_CALL(const char* glVersion = (const char*)glGetString(GL_VERSION));
        LD_CORE_INFO("  Vendor: {0}", glVendor);
        LD_CORE_INFO("  Renderer: {0}", glRenderer);
        LD_CORE_INFO("  Version: {0}", glVersion);

        if (GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5)) {
            LD_CORE_CRITICAL("Lada requires at least OpenGL version 4.5!");
        }

        if (const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !status) {
            LD_CORE_CRITICAL("GLAD could not be initialized");
        }
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(static_cast<GLFWwindow *>(m_Window.GetNativeWindow()));
    }
}
