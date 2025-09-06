#include "VulkanShader.h"

#include "app/Logger.h"

namespace Lada {
    VulkanShader::VulkanShader(const std::string &shaderPath,
                               const std::shared_ptr<VulkanGraphicsContext> &graphicsContext)
        : m_GraphicsContext(graphicsContext) {
    }

    void VulkanShader::createShaderModule(const std::vector<char> &code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

        LD_VK_ASSERT_SUCCESS(vkCreateShaderModule(m_GraphicsContext->GetDevice()->NativeDevice(),
                                 &createInfo, nullptr, &m_ShaderModule), "Could not create shader module!");
    }
}
