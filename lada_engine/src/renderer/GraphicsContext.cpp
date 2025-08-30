#include "ldpch.h"
#include "GraphicsContext.h"

#include "../platform/glfw/GlfwWindow.h"
#include "platform/opengl/OpenGLContext.h"
#include "platform/vulkan/VulkanContext.h"

namespace Lada {
    std::shared_ptr<GraphicsContext> GraphicsContext::Create(void *window, const GraphicAPI api) {
        switch (api) {
            case GraphicAPI::OPENGL:
                return std::make_shared<OpenGLContext>(static_cast<GLFWwindow*>(window));
            case GraphicAPI::VULKAN:
                return std::make_shared<VulkanContext>(static_cast<GLFWwindow*>(window));
            default:
                throw std::runtime_error("Unsupported API");
        }
    }
}
