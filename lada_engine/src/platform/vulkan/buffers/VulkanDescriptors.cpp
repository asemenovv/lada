#include "VulkanDescriptors.h"

#include <cassert>

#include "platform/vulkan/VulkanGraphicsContext.h"
#include "renderer/GraphicsContext.h"

namespace Lada {
    // *************** Descriptor Set Layout Builder *********************

    VulkanDescriptorSetLayout::Builder &VulkanDescriptorSetLayout::Builder::AddBinding(const uint32_t binding,
                                                                           const DescriptorType descriptorType,
                                                                           const ShaderStage stageFlags,
                                                                           const uint32_t count) {
        assert(!m_Bindings.contains(binding) && "Binding already in use");
        VkDescriptorSetLayoutBinding layoutBinding = {};
        layoutBinding.binding = binding;
        layoutBinding.descriptorCount = count;
        layoutBinding.descriptorType = toVkDescriptorType(descriptorType);
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBinding.stageFlags = static_cast<VkShaderStageFlags>(stageFlags);
        m_Bindings[binding] = layoutBinding;
        return *this;
    }

    std::unique_ptr<VulkanDescriptorSetLayout> VulkanDescriptorSetLayout::Builder::Build() const {
        return std::make_unique<VulkanDescriptorSetLayout>(m_GraphicsContext, m_Bindings);
    }

    // *************** Descriptor Set Layout *********************

    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(GraphicsContext* graphicsContext,
                                             const std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> &bindings)
        : m_GraphicsContext(static_cast<VulkanGraphicsContext*>(graphicsContext)), m_Bindings(bindings) {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings{};
        for (auto kv: bindings) {
            setLayoutBindings.push_back(kv.second);
        }

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
        descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
        descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

        if (vkCreateDescriptorSetLayout(m_GraphicsContext->GetDevice().NativeDevice(), &descriptorSetLayoutInfo,
                                        nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout() {
        vkDestroyDescriptorSetLayout(m_GraphicsContext->GetDevice().NativeDevice(), m_DescriptorSetLayout, nullptr);
    }

    // *************** Descriptor Pool Builder *********************

    VkDescriptorType VulkanDescriptorSetLayout::toVkDescriptorType(DescriptorType descriptor) {
        switch (descriptor) {
            case DescriptorType::UniformBuffer:
                return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            case DescriptorType::CombinedImageSampler:
                return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        }
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }

    DescriptorPool::Builder::Builder(GraphicsContext *graphicsContext)
        : m_GraphicsContext(static_cast<VulkanGraphicsContext*>(graphicsContext)) {}

    DescriptorPool::Builder &DescriptorPool::Builder::AddPoolSize(const VkDescriptorType descriptorType,
                                                                  const uint32_t count) {
        m_PoolSizes.push_back({descriptorType, count});
        return *this;
    }

    DescriptorPool::Builder &DescriptorPool::Builder::SetPoolFlags(const VkDescriptorPoolCreateFlags flags) {
        m_PoolFlags = flags;
        return *this;
    }

    DescriptorPool::Builder &DescriptorPool::Builder::SetMaxSets(const uint32_t count) {
        m_MaxSets = count;
        return *this;
    }

    std::unique_ptr<DescriptorPool> DescriptorPool::Builder::Build() const {
        return std::make_unique<DescriptorPool>(m_GraphicsContext, m_MaxSets, m_PoolFlags, m_PoolSizes);
    }

    // *************** Descriptor Pool *********************

    DescriptorPool::DescriptorPool(GraphicsContext* graphicsContext, uint32_t maxSets,
                                   VkDescriptorPoolCreateFlags poolFlags,
                                   const std::vector<VkDescriptorPoolSize> &poolSizes)
        : m_GraphicsContext(static_cast<VulkanGraphicsContext*>(graphicsContext)) {
        VkDescriptorPoolCreateInfo descriptorPoolInfo{};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = maxSets;
        descriptorPoolInfo.flags = poolFlags;

        if (vkCreateDescriptorPool(m_GraphicsContext->GetDevice().NativeDevice(), &descriptorPoolInfo,
                                   nullptr, &m_DescriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    DescriptorPool::~DescriptorPool() {
        vkDestroyDescriptorPool(m_GraphicsContext->GetDevice().NativeDevice(), m_DescriptorPool, nullptr);
    }

    bool DescriptorPool::AllocateDescriptor(const VkDescriptorSetLayout descriptorSetLayout,
                                            VkDescriptorSet &descriptor) const {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = m_DescriptorPool;
        allocInfo.pSetLayouts = &descriptorSetLayout;
        allocInfo.descriptorSetCount = 1;

        // Might want to create a "DescriptorPoolManager" class that handles this case, and builds
        // a new pool whenever an old pool fills up. But this is beyond our current scope
        if (vkAllocateDescriptorSets(m_GraphicsContext->GetDevice().NativeDevice(), &allocInfo, &descriptor) !=
            VK_SUCCESS) {
            return false;
        }
        return true;
    }

    void DescriptorPool::FreeDescriptors(const std::vector<VkDescriptorSet> &descriptors) const {
        vkFreeDescriptorSets(m_GraphicsContext->GetDevice().NativeDevice(), m_DescriptorPool,
            static_cast<uint32_t>(descriptors.size()), descriptors.data());
    }

    void DescriptorPool::ResetPool() const {
        vkResetDescriptorPool(m_GraphicsContext->GetDevice().NativeDevice(), m_DescriptorPool, 0);
    }

    // *************** Descriptor Writer *********************

    VulkanDescriptorWriter::VulkanDescriptorWriter(VulkanDescriptorSetLayout& setLayout, DescriptorPool& pool)
    : m_SetLayout(setLayout), m_Pool(pool) {}

    VulkanDescriptorWriter& VulkanDescriptorWriter::WriteBuffer(const uint32_t binding, const VkDescriptorBufferInfo* bufferInfo) {
        const auto& bindingDescription = m_SetLayout.m_Bindings[binding];

        assert(bindingDescription.descriptorCount == 1 && "Binding single descriptor info, but binding expects multiple");

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.descriptorType = bindingDescription.descriptorType;
        write.dstBinding = binding;
        write.pBufferInfo = bufferInfo;
        write.descriptorCount = 1;

        m_Writes.push_back(write);
        return *this;
    }

    VulkanDescriptorWriter& VulkanDescriptorWriter::WriteImage(const uint32_t binding, const VkDescriptorImageInfo* imageInfo) {
        assert(m_SetLayout.m_Bindings.count(binding) == 1 && "Layout does not contain specified binding");

        const auto& bindingDescription = m_SetLayout.m_Bindings[binding];

        assert(bindingDescription.descriptorCount == 1 && "Binding single descriptor info, but binding expects multiple");

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.descriptorType = bindingDescription.descriptorType;
        write.dstBinding = binding;
        write.dstArrayElement = 0;
        write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        write.descriptorCount = 1;
        write.pImageInfo = imageInfo;

        m_Writes.push_back(write);
        return *this;
    }

    bool VulkanDescriptorWriter::Build(VkDescriptorSet& set) {
        const bool success = m_Pool.AllocateDescriptor(m_SetLayout.GetDescriptorSetLayout(), set);
        if (!success) {
            return false;
        }
        Overwrite(set);
        return true;
    }

    void VulkanDescriptorWriter::Overwrite(VkDescriptorSet &set) {
        for (auto &write : m_Writes) {
            write.dstSet = set;
        }
        vkUpdateDescriptorSets(m_Pool.m_GraphicsContext->GetDevice().NativeDevice(),
            m_Writes.size(), m_Writes.data(),
            0, nullptr);
    }
}
