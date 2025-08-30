#pragma once

#include "VulkanInstance.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lada {
    class VulkanContext final : public GraphicsContext {
    public:
        explicit VulkanContext(GLFWwindow *window);
        ~VulkanContext() override = default;

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
        std::unique_ptr<VulkanInstance> m_VulkanInstance;
    };
}
