#include "ldpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"
#include "RenderPass.h"
#include "app/Logger.h"
#include "model/Model.h"

namespace Lada::Render {
    Renderer::Renderer(const Window &window, GraphicsContext *graphicsContext)
        : m_GraphicsContext(graphicsContext), m_Camera(nullptr) {
        m_Camera = CameraBuilder()
                .Screen(45.0, window.GetWidth() / window.GetHeight(), 1.0, 100.0)
                .Position({0.0, 0.0, 0.0})
                .ViewDirection({0.0, 0.0, 1.0})
                .UpDirection({0.0, 1.0, 0.0})
                .Build();
        m_CommandBuffer = m_GraphicsContext->CreateCommandBuffer();
    }

    void Renderer::Init() {
        // GL_CALL(glClearColor());
    }

    void Renderer::Shutdown() {
    }

    CommandBuffer *Renderer::BeginFrame() {
        const RenderPass *renderPass = m_GraphicsContext->GetPipeline()->GetRenderPass();
        if (!m_GraphicsContext->GetSwapChain()->AcquireNextImage(&m_CurrentImageIndex)) {
            LD_CORE_ERROR("Failed to acquire image from SwapChain");
        }
        m_CommandBuffer->Reset();
        m_CommandBuffer->Begin();
        renderPass->Begin(m_CommandBuffer.get(), 0, m_ClearColor);
        m_GraphicsContext->GetPipeline()->Bind(m_CommandBuffer.get());
        renderPass->SetViewportAndScissor(m_CommandBuffer.get(), m_Camera->GetViewport(), m_Camera->GetScissor());
        return m_CommandBuffer.get();
    }

    void Renderer::Submit(const std::shared_ptr<Model> &model) const {
        m_CommandBuffer->Draw(3);
        // for (Model::SubMesh subMesh : *model) {
        // model->BindMaterial(subMesh.material, m_Camera->GetProjectionMatrix(), m_Camera->GetViewMatrix());
        // subMesh.mesh->Draw();
        // }
    }

    void Renderer::EndFrame() {
        const RenderPass *renderPass = m_GraphicsContext->GetPipeline()->GetRenderPass();
        renderPass->End(m_CommandBuffer.get());
        m_CommandBuffer->End();
        if (!m_GraphicsContext->GetSwapChain()->SubmitCommandBuffer(m_CommandBuffer.get(), &m_CurrentImageIndex)) {
            LD_CORE_ERROR("Failed to submit command buffer");
        }
    }
}
