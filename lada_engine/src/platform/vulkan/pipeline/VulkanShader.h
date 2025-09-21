#pragma once

#include <vulkan/vulkan.h>

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanShader {
    public:
        VulkanShader(const std::string &shaderPath, VulkanGraphicsContext* graphicsContext);

        ~VulkanShader();

        [[nodiscard]] VkShaderModule NativeShader() const { return m_ShaderModule; }

    private:
        void createShaderModule(const std::vector<char> &code);

        static std::vector<char> readFile(const std::string &filePath);

        VkShaderModule m_ShaderModule;
        VulkanGraphicsContext* m_GraphicsContext;
    };
}
