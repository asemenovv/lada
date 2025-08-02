#include "ldpch.h"
#include "GraphicsContext.h"

#include "../platform/glfw/GlfwWindow.h"
#include "platform/opengl/OpenGLContext.h"

namespace Lada {
    std::shared_ptr<GraphicsContext> GraphicsContext::Create(void* window) {
        return std::make_shared<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }
}
