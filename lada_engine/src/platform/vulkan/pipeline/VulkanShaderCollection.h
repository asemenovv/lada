#pragma once

#include "VulkanShader.h"

namespace Lada {
    class GraphicsContext;
}

namespace Lada {
    class ShaderCollection {
    public:
        ShaderCollection(GraphicsContext *graphicsContext, std::string vertexShaderFilePath,
                         std::string fragmentShaderFilePath);

        ~ShaderCollection();

        VkDescriptorSetLayout CreateDescriptorSetLayout();

        VulkanShader* GetShader(ShaderStage stage) const;

    private:
        std::unique_ptr<VulkanShader> m_VertexShader;

        std::unique_ptr<VulkanShader> m_FragmentShader;

        VulkanGraphicsContext *m_GraphicsContext;

        VkDescriptorSetLayout m_DescriptorSetLayout;

        static VkDescriptorType vkDescriptorType(DescriptorType descriptorType);
    };
}
