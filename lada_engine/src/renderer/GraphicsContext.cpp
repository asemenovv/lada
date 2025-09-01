#include "ldpch.h"
#include "GraphicsContext.h"

#include "../platform/glfw/GlfwWindow.h"
#include "platform/opengl/OpenGLContext.h"
#include "platform/vulkan/VulkanContext.h"

namespace Lada {
    std::shared_ptr<GraphicsContext> GraphicsContext::Create(const std::shared_ptr<Window>& window, const GraphicAPI api) {
        switch (api) {
            case GraphicAPI::OPENGL:
                return std::make_shared<OpenGLContext>(window);
            case GraphicAPI::VULKAN:
                return std::make_shared<VulkanContext>(window);
            default:
                throw std::runtime_error("Unsupported API");
        }
    }
}
