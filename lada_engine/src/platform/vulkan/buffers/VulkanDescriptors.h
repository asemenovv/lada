#pragma once

#include <unordered_map>

#include "platform/vulkan/pipeline/VulkanPipelineLayout.h"
#include "platform/vulkan/pipeline/VulkanShaderCompiler.h"

namespace Lada {
    enum class DescriptorType;
    class GraphicsContext;

    class VulkanDescriptorSetLayout {
    public:
        class Builder {
        public:
            explicit Builder(GraphicsContext* graphicsContext)
                : m_GraphicsContext(graphicsContext) {
            }

            Builder &AddBinding(uint32_t binding, DescriptorType descriptorType,\
                                ShaderStage stageFlags, uint32_t count = 1);
            std::unique_ptr<VulkanDescriptorSetLayout> Build() const;
        private:
            GraphicsContext* m_GraphicsContext;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> m_Bindings{};
        };

        VulkanDescriptorSetLayout(GraphicsContext* graphicsContext,
            const std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> &bindings);
        ~VulkanDescriptorSetLayout();

        VulkanDescriptorSetLayout(const VulkanDescriptorSetLayout &) = delete;
        VulkanDescriptorSetLayout &operator=(const VulkanDescriptorSetLayout &) = delete;

        VkDescriptorSetLayout GetDescriptorSetLayout() const { return m_DescriptorSetLayout; }

    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkDescriptorSetLayout m_DescriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> m_Bindings;

        friend class VulkanDescriptorWriter;

        static VkDescriptorType toVkDescriptorType(DescriptorType descriptor);
    };

    class DescriptorPool {
    public:
        class Builder {
        public:
            explicit Builder(GraphicsContext* graphicsContext);

            Builder& AddPoolSize(VkDescriptorType descriptorType, uint32_t count);
            Builder& SetPoolFlags(VkDescriptorPoolCreateFlags flags);
            Builder& SetMaxSets(uint32_t count);
            std::unique_ptr<DescriptorPool> Build() const;

        private:
            VulkanGraphicsContext* m_GraphicsContext;
            std::vector<VkDescriptorPoolSize> m_PoolSizes{};
            uint32_t m_MaxSets = 1000;
            VkDescriptorPoolCreateFlags m_PoolFlags = 0;
        };

        DescriptorPool(GraphicsContext* graphicsContext, uint32_t maxSets,
            VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& poolSizes);
        ~DescriptorPool();
        DescriptorPool(const DescriptorPool &) = delete;
        DescriptorPool &operator=(const DescriptorPool &) = delete;

        bool AllocateDescriptor(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;
        void FreeDescriptors(const std::vector<VkDescriptorSet> &descriptors) const;
        void ResetPool() const;
    private:
        VulkanGraphicsContext* m_GraphicsContext;
        VkDescriptorPool m_DescriptorPool;

        friend class VulkanDescriptorWriter;
    };

    class VulkanDescriptorWriter {
    public:
        VulkanDescriptorWriter(VulkanDescriptorSetLayout& setLayout, DescriptorPool& pool);

        VulkanDescriptorWriter& WriteBuffer(uint32_t binding, const VkDescriptorBufferInfo* bufferInfo);
        VulkanDescriptorWriter& WriteImage(uint32_t binding, const VkDescriptorImageInfo* imageInfo);

        bool Build(VkDescriptorSet &set);
        void Overwrite(VkDescriptorSet &set);

    private:
        VulkanDescriptorSetLayout &m_SetLayout;
        DescriptorPool &m_Pool;
        std::vector<VkWriteDescriptorSet> m_Writes;
    };
}
