#include "VulkanShader.h"

#include "app/Logger.h"

namespace Lada {
    VulkanShader::VulkanShader(const std::string &shaderPath,
                               const std::shared_ptr<VulkanGraphicsContext> &graphicsContext)
        : m_GraphicsContext(graphicsContext) {
        const auto code = readFile(shaderPath);
        createShaderModule(code);
    }

    void VulkanShader::createShaderModule(const std::vector<char> &code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

        LD_VK_ASSERT_SUCCESS(vkCreateShaderModule(m_GraphicsContext->GetDevice().NativeDevice(),
                                 &createInfo, nullptr, &m_ShaderModule), "Could not create shader module!");
    }

    std::vector<char> VulkanShader::readFile(const std::string &filePath) {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file " + filePath);
        }
        const auto fileSize = static_cast<long>(file.tellg());
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }
}
