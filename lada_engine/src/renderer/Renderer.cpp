#include "ldpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"
#include "RenderPass.h"
#include "Uniforms.h"
#include "app/Logger.h"
#include "events/ApplicationEvent.h"
#include "model/Model.h"
#include "platform/vulkan/buffers/VulkanUniformBuffer.h"

namespace Lada::Render {
    Renderer::Renderer(const Window &window, GraphicsContext *graphicsContext, EventManager *eventManager)
        : m_GraphicsContext(graphicsContext), m_Camera(nullptr), m_CurrentImageIndex(0), m_CurrentFrameIndex(0), m_EventManager(eventManager) {
        m_Camera = CameraBuilder()
                .Screen(45.0, window.GetWidth() / window.GetHeight(), 1.0, 100.0)
                .Position({0.0, 0.0, 0.0})
                .ViewDirection({0.0, 0.0, 1.0})
                .UpDirection({0.0, 1.0, 0.0})
                .Build();
        m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            m_CommandBuffers[i] = m_GraphicsContext->CreateCommandBuffer();
        }
        m_EventManager->BIND_HANDLER(WindowResizeEvent, Renderer::OnWindowResizeEvent);
        m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            m_UniformBuffers[i] = std::make_unique<VulkanUniformBuffer>(m_GraphicsContext, sizeof(GlobalUbo));
            m_UniformBuffers[i]->Map();
        }
    }

    void Renderer::Init() {
        // GL_CALL(glClearColor());
    }

    void Renderer::Shutdown() {
    }

    CommandBuffer *Renderer::BeginFrame() {
        const RenderPass *renderPass = m_GraphicsContext->GetPipeline()->GetRenderPass();
        RenderStatus status = m_GraphicsContext->GetSwapChain()->AcquireNextImage(&m_CurrentImageIndex, m_CurrentFrameIndex);
        if (status == RenderStatus::FAILED) {
            LD_CORE_ERROR("Failed to acquire image from SwapChain");
            std::abort();
        }
        if (status == RenderStatus::OUT_OF_DATE_SWAP_CHAIN) {
            m_GraphicsContext->RecreateSwapChain();
            return nullptr;
        }
        m_CommandBuffers[m_CurrentFrameIndex]->Reset();
        m_CommandBuffers[m_CurrentFrameIndex]->Begin(false);
        renderPass->Begin(m_CommandBuffers[m_CurrentFrameIndex].get(), m_CurrentImageIndex, m_ClearColor);
        m_GraphicsContext->GetPipeline()->Bind(m_CommandBuffers[m_CurrentFrameIndex].get());
        renderPass->SetViewportAndScissor(m_CommandBuffers[m_CurrentFrameIndex].get(), m_Camera->GetViewport(),
                                          m_Camera->GetScissor());
        return m_CommandBuffers[m_CurrentFrameIndex].get();
    }

    void Renderer::Submit(const Mesh* mesh) const {
        mesh->GetVertexBuffer()->Bind(m_CommandBuffers[m_CurrentFrameIndex].get());
        mesh->GetIndexBuffer()->Bind(m_CommandBuffers[m_CurrentFrameIndex].get());
        m_CommandBuffers[m_CurrentFrameIndex]->DrawIndexed(mesh->GetIndexCount());
        // for (Model::SubMesh subMesh : *model) {
        // model->BindMaterial(subMesh.material, m_Camera->GetProjectionMatrix(), m_Camera->GetViewMatrix());
        // subMesh.mesh->Draw();
        // }
    }

    void Renderer::Update() const {
        struct SwapChain::Extent extent = m_GraphicsContext->GetSwapChain()->Extent();
        GlobalUbo ubo {};
        ubo.proj = m_Camera->GetProjectionMatrix();
        ubo.view = m_Camera->GetViewMatrix();
        ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        m_UniformBuffers[m_CurrentFrameIndex]->WriteToBuffer(&ubo, sizeof(ubo), 0);
    }

    void Renderer::EndFrame() {
        const RenderPass *renderPass = m_GraphicsContext->GetPipeline()->GetRenderPass();
        renderPass->End(m_CommandBuffers[m_CurrentFrameIndex].get());
        m_CommandBuffers[m_CurrentFrameIndex]->End();
        if (!m_GraphicsContext->GetSwapChain()->SubmitCommandBuffer(m_CommandBuffers[m_CurrentFrameIndex].get(),
                                                                    &m_CurrentImageIndex, m_CurrentFrameIndex)) {
            LD_CORE_ERROR("Failed to submit command buffer");
        }
        RenderStatus status = m_GraphicsContext->GetSwapChain()->Present(&m_CurrentImageIndex, m_CurrentFrameIndex);
        if (status == RenderStatus::FAILED) {
            LD_CORE_ERROR("Presentation failed");
            std::abort();
        }
        if (status == RenderStatus::OUT_OF_DATE_SWAP_CHAIN || status == RenderStatus::SUBOPTIMAL_SWAP_CHAIN) {
            m_GraphicsContext->RecreateSwapChain();
        }
        m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    bool Renderer::OnWindowResizeEvent(const WindowResizeEvent &event) const {
        m_GraphicsContext->RecreateSwapChain();
        return true;
    }
}
