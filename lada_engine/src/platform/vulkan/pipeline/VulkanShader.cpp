#include "VulkanShader.h"

#include <spirv_reflect.h>

#include "VulkanShaderCompiler.h"
#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    VulkanShader::VulkanShader(const std::string &shaderPath, VulkanGraphicsContext* graphicsContext, const ShaderStage stage)
        : m_ShaderStage(stage), m_ShaderModule(nullptr), m_GraphicsContext(graphicsContext) {
        const auto code = readFile(shaderPath);
        const VulkanShaderCompiler compiler(true, true);
        const CompileResult compiledShader = compiler.CompileString(code, stage);
        createShaderModule(compiledShader);
        createDescriptors(compiledShader);
    }

    VulkanShader::~VulkanShader() {
        vkDestroyShaderModule(m_GraphicsContext->GetDevice().NativeDevice(), m_ShaderModule, nullptr);
    }

    void VulkanShader::createShaderModule(const CompileResult &code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.spirv.size() * sizeof(uint32_t);
        createInfo.pCode = code.spirv.data();

        LD_VK_ASSERT_SUCCESS(vkCreateShaderModule(m_GraphicsContext->GetDevice().NativeDevice(),
                                 &createInfo, nullptr, &m_ShaderModule), "Could not create shader module!");
    }

    void VulkanShader::createDescriptors(const CompileResult &code) {
        SpvReflectShaderModule module;
        SpvReflectResult result = spvReflectCreateShaderModule(
            code.spirv.size() * sizeof(uint32_t),
            code.spirv.data(),
            &module
        );
        LD_CORE_ASSERT_WITH_ERROR(SPV_REFLECT_RESULT_SUCCESS == result, "Failed to run shader reflection");
        m_EntryPoint = module.entry_point_name;
        uint32_t count = 0;
        spvReflectEnumerateDescriptorBindings(&module, &count, nullptr);
        std::vector<SpvReflectDescriptorBinding*> bindings(count);
        spvReflectEnumerateDescriptorBindings(&module, &count, bindings.data());
        for (const auto* b : bindings) {
            if (b->descriptor_type == SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
                std::cout << "UBO " << b->name
                          << " binding=" << b->binding
                          << " set=" << b->set
                          << " size=" << b->block.size << "\n";
                for (uint32_t i = 0; i < b->block.member_count; ++i) {
                    const auto& m = b->block.members[i];
                    std::cout << "  " << m.name << " offset=" << m.offset << "\n";
                }
            }
        }
        spvReflectDestroyShaderModule(&module);
    }

    std::string VulkanShader::readFile(const std::string &filePath) {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file " + filePath);
        }
        const auto fileSize = static_cast<long>(file.tellg());
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        std::ostringstream contents;
        contents << file.rdbuf();
        return contents.str();
    }
}
