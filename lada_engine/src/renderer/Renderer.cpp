#include "ldpch.h"
#include "Renderer.h"
#include "app/GlCall.h"
#include "model/Model.h"

namespace Lada::Render {
    Renderer::Renderer(const std::shared_ptr<Window>& window, const std::shared_ptr<GraphicsContext>& graphicsContext)
    : m_GraphicsContext(graphicsContext), m_Camera(nullptr) {
        m_Camera = CameraBuilder()
                .Screen(45.0, window->GetWidth() / window->GetHeight(), 1.0, 100.0)
                .Position({0.0, 0.0, 0.0})
                .ViewDirection({0.0, 0.0, 1.0})
                .UpDirection({0.0, 1.0, 0.0})
                .Build();
    }

    void Renderer::Init() {
        GL_CALL(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
    }

    void Renderer::Shutdown() {
    }

    void Renderer::BeginFrame() {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Submit(const std::shared_ptr<Model>& model) const {
        for (Model::SubMesh subMesh : *model) {
            model->BindMaterial(subMesh.material, m_Camera->GetProjectionMatrix(), m_Camera->GetViewMatrix());
            subMesh.mesh->Draw();
        }
    }

    void Renderer::EndFrame() {
        m_GraphicsContext->SwapBuffers();
    }
}
