#include "VulkanShaderCollection.h"

#include <ranges>

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    ShaderCollection::ShaderCollection(GraphicsContext *graphicsContext, std::string vertexShaderFilePath,
                                       std::string fragmentShaderFilePath)
        : m_VertexShader(nullptr), m_FragmentShader(nullptr),
          m_GraphicsContext(static_cast<VulkanGraphicsContext *>(graphicsContext)), m_DescriptorSetLayout(nullptr) {
        m_VertexShader = std::make_unique<VulkanShader>(vertexShaderFilePath, m_GraphicsContext, ShaderStage::Vertex);
        m_FragmentShader = std::make_unique<VulkanShader>(fragmentShaderFilePath, m_GraphicsContext,
                                                          ShaderStage::Fragment);
    }

    ShaderCollection::~ShaderCollection() {
        vkDestroyDescriptorSetLayout(m_GraphicsContext->GetDevice().NativeDevice(), m_DescriptorSetLayout, nullptr);
    }

    VkDescriptorSetLayout ShaderCollection::CreateDescriptorSetLayout() {
        if (m_DescriptorSetLayout) {
            return m_DescriptorSetLayout;
        }
        std::unordered_set<uint32_t> alreadyDefinedBindings;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> layoutBindings;
        for (auto binding: m_VertexShader->GetDescriptorSetBindings()) {
            VkDescriptorSetLayoutBinding layoutBinding{};
            layoutBinding.binding = binding.second.Binding;
            layoutBinding.descriptorType = vkDescriptorType(binding.second.DescriptorType);
            layoutBinding.descriptorCount = binding.second.DescriptorsCount;
            layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
            layoutBinding.pImmutableSamplers = nullptr;
            layoutBindings[binding.second.Binding] = layoutBinding;
            alreadyDefinedBindings.insert(binding.second.Binding);
        }
        for (auto binding: m_FragmentShader->GetDescriptorSetBindings()) {
            // TODO: Validation that structure is the same
            if (alreadyDefinedBindings.contains(binding.second.Binding)) {
                layoutBindings[binding.second.Binding].stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
            }
        }

        std::vector<VkDescriptorSetLayoutBinding> bindings{
            std::ranges::begin(layoutBindings | std::views::values),
            std::ranges::end(layoutBindings | std::views::values)
        };

        if (bindings.size() == 0) {
            return nullptr;
        }

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = bindings.size();
        layoutInfo.pBindings = bindings.data();

        LD_VK_ASSERT_SUCCESS(
            vkCreateDescriptorSetLayout(m_GraphicsContext->GetDevice().NativeDevice(), &layoutInfo, nullptr, &
                m_DescriptorSetLayout),
            "Failed to create descriptor set layout!");
        return m_DescriptorSetLayout;
    }

    VulkanShader * ShaderCollection::GetShader(const ShaderStage stage) const {
        switch (stage) {
            case ShaderStage::Vertex:
                return m_VertexShader.get();
            case ShaderStage::Fragment:
                return m_FragmentShader.get();
            default:
                return nullptr;
        }
    }

    VkDescriptorType ShaderCollection::vkDescriptorType(const DescriptorType descriptorType) {
        switch (descriptorType) {
            case DescriptorType::UniformBuffer:
                return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            case DescriptorType::CombinedImageSampler:
                return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            default:
                return VK_DESCRIPTOR_TYPE_MAX_ENUM;
        }
    }
}
