#pragma once

#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    class VulkanImage {
    public:
        VulkanImage() noexcept
            : m_Image(VK_NULL_HANDLE)
              //, m_ImageMemory(VK_NULL_HANDLE),
              // m_ImageView(VK_NULL_HANDLE)
        {}

        VulkanImage(VulkanGraphicsContext* graphicsContext, VkImage image,
            VkFormat format, const VkImageAspectFlags aspectFlags, const std::string& name);

        ~VulkanImage();

        VulkanImage(const VulkanImage &) = delete;

        VulkanImage &operator=(const VulkanImage &) = delete;

        VulkanImage(VulkanImage &&other) noexcept;

        VulkanImage &operator=(VulkanImage &&other) noexcept;

        VkFormat GetFormat() const { return m_Format; }

        VkImageView GetView() const { return m_ImageView; }

    private:
        void reset();

        void createImageView(VkFormat format, VkImageAspectFlags aspectFlags, const std::string& name);

        VkImage m_Image;
        VkImageView m_ImageView;
        VkFormat m_Format;
        VulkanGraphicsContext* m_GraphicsContext;
        bool m_ResetImage = true;
    };
}
