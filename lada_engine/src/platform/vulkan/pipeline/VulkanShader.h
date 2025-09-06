#pragma once

#include <vulkan/vulkan.h>

#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    class VulkanShader {
    public:
        VulkanShader(const std::string &shaderPath, const std::shared_ptr<VulkanGraphicsContext> &graphicsContext);

        ~VulkanShader();

        [[nodiscard]] VkShaderModule NativeShader() const { return m_ShaderModule; }

    private:
        void createShaderModule(const std::vector<char> &code);

        VkShaderModule m_ShaderModule;
        std::shared_ptr<VulkanGraphicsContext> m_GraphicsContext;
    };
}
