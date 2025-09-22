#include "VulkanImage.h"

#include "app/Logger.h"

namespace Lada {
    VulkanImage::VulkanImage(VulkanGraphicsContext* graphicsContext, const VkImage image,
        const VkFormat format, const VkImageAspectFlags aspectFlags, const std::string& name)
        : m_Image(image), m_Format(format), m_GraphicsContext(graphicsContext) {
        m_GraphicsContext->SetDebugName(reinterpret_cast<uint64_t>(image), VK_OBJECT_TYPE_IMAGE, name.c_str());
        m_Image = image;
        m_ResetImage = false;
        createImageView(m_Format, aspectFlags, name);
    }

    VulkanImage::~VulkanImage() {
        reset();
    }

    VulkanImage::VulkanImage(VulkanImage &&other) noexcept {
        *this = std::move(other);
        m_GraphicsContext = other.m_GraphicsContext;
    }

    VulkanImage &VulkanImage::operator=(VulkanImage &&other) noexcept {
        if (this != &other) {
            reset();
            m_GraphicsContext = std::move(other.m_GraphicsContext);
            m_Image = other.m_Image;
            // m_ImageMemory = other.m_ImageMemory;
            m_ImageView = other.m_ImageView;
            m_Format = other.m_Format;
            m_ResetImage = other.m_ResetImage;

            other.m_Image = VK_NULL_HANDLE;
            // other.m_ImageMemory = VK_NULL_HANDLE;
            other.m_ImageView = VK_NULL_HANDLE;
            other.m_Format = VK_FORMAT_UNDEFINED;
            other.m_ResetImage = true;
        }
        return *this;
    }

    void VulkanImage::reset() {
        if (m_GraphicsContext) {
            const auto device = m_GraphicsContext->GetDevice().NativeDevice();
            if (m_ImageView) {
                vkDestroyImageView(device, m_ImageView, nullptr);
                m_ImageView = VK_NULL_HANDLE;
            }
            if (m_ResetImage && m_Image) {
                vkDestroyImage(device, m_Image, nullptr);
                m_Image = VK_NULL_HANDLE;
            }
            // if (m_ResetImage && m_ImageMemory) {
                // vkFreeMemory(device, m_ImageMemory, nullptr);
                // m_ImageMemory = VK_NULL_HANDLE;
            // }
        } else {
            m_ImageView = VK_NULL_HANDLE;
            m_Image = VK_NULL_HANDLE;
            // m_ImageMemory = VK_NULL_HANDLE;
        }
    }

    void VulkanImage::createImageView(const VkFormat format, const VkImageAspectFlags aspectFlags, const std::string& name) {
        const auto device = m_GraphicsContext->GetDevice().NativeDevice();
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = m_Image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;
        LD_VK_ASSERT_SUCCESS(vkCreateImageView(device, &viewInfo, nullptr, &m_ImageView),
            "Failed to create texture image view!");
        m_GraphicsContext->SetDebugName(reinterpret_cast<uint64_t>(m_ImageView), VK_OBJECT_TYPE_IMAGE_VIEW, (name + "->ImageView").c_str());
    }
}
