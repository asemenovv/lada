#include "GraphicsApiFactory.h"

#include "platform/opengl/OpenGLContext.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    std::unique_ptr<GraphicsContext> GraphicsApiFactory::CreateContext(const std::shared_ptr<Window> &window) const {
            switch (m_GraphicAPI) {
                case GraphicAPI::OPENGL:
                    return std::make_unique<OpenGLContext>(window);
                case GraphicAPI::VULKAN:
                    return std::make_unique<VulkanGraphicsContext>(window);
                default:
                    throw std::runtime_error("Unsupported API");
            }
    }
}
