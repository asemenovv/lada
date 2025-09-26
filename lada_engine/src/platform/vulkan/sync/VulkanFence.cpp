#include "VulkanFence.h"

#include "app/Logger.h"
#include "platform/vulkan/VulkanGraphicsContext.h"

namespace Lada {
    VulkanFence::VulkanFence(VulkanGraphicsContext *graphicsContext, const std::string &name, const bool signaled) : m_GraphicsContext(graphicsContext) {
        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        if (signaled) {
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        } else {
            fenceInfo.flags = 0;
        }
        LD_VK_ASSERT_SUCCESS(
            vkCreateFence(m_GraphicsContext->GetDevice().NativeDevice(), &fenceInfo, nullptr, &m_Fence),
            "Failed to create fence!");
        m_GraphicsContext->SetDebugName(reinterpret_cast<uint64_t>(m_Fence), VK_OBJECT_TYPE_FENCE, name.c_str());
    }

    VulkanFence::~VulkanFence() {
        vkDestroyFence(m_GraphicsContext->GetDevice().NativeDevice(), m_Fence, nullptr);
    }

    void VulkanFence::Wait() {
        vkWaitForFences(m_GraphicsContext->GetDevice().NativeDevice(), 1, &m_Fence, VK_TRUE, UINT64_MAX);
    }

    void VulkanFence::Reset() {
        vkResetFences(m_GraphicsContext->GetDevice().NativeDevice(), 1, &m_Fence);
    }
}
