#pragma once

#include <vulkan/vulkan.h>

#include "VulkanShaderCompiler.h"

namespace Lada {
    class VulkanGraphicsContext;

    class VulkanShader {
    public:
        VulkanShader(const std::string &shaderPath, VulkanGraphicsContext* graphicsContext, ShaderStage stage);

        ~VulkanShader();

        [[nodiscard]] VkShaderModule NativeShader() const { return m_ShaderModule; }

        std::string GetEntryPointName() const { return m_EntryPoint; }

    private:
        void createShaderModule(const CompileResult &code);

        void createDescriptors(const CompileResult& code);

        static std::string readFile(const std::string &filePath);

        ShaderStage m_ShaderStage;
        VkShaderModule m_ShaderModule;
        VulkanGraphicsContext* m_GraphicsContext;
        std::string m_EntryPoint = "main";
    };
}
