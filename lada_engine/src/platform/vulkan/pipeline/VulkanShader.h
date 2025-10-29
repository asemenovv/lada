#pragma once

#include <vulkan/vulkan.h>

#include "VulkanShaderCompiler.h"

namespace Lada {
    class VulkanGraphicsContext;

    enum class DescriptorType {
        UniformBuffer,
        CombinedImageSampler
    };

    struct DescriptorSetLayoutBinding {
        std::string Name;
        DescriptorType DescriptorType;
        uint32_t Binding;
        uint32_t Set;
        uint32_t DescriptorsCount = 1;
        uint32_t DataSize = 0;
    };

    class VulkanShader {
    public:
        VulkanShader(const std::string &shaderPath, VulkanGraphicsContext* graphicsContext, ShaderStage stage);

        ~VulkanShader();

        [[nodiscard]] VkShaderModule NativeShader() const { return m_ShaderModule; }

        std::string GetEntryPointName() const { return m_EntryPoint; }

        std::unordered_map<uint32_t, DescriptorSetLayoutBinding> GetDescriptorSetBindings() const { return m_DescriptorSetLayoutBindings; }

    private:
        void createShaderModule(const CompileResult &code);

        void createDescriptors(const CompileResult& code);

        static std::string readFile(const std::string &filePath);

        ShaderStage m_ShaderStage;
        VkShaderModule m_ShaderModule;
        VulkanGraphicsContext* m_GraphicsContext;
        std::string m_EntryPoint = "main";
        std::unordered_map<uint32_t, DescriptorSetLayoutBinding>  m_DescriptorSetLayoutBindings;
    };
}
