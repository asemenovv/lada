#include "ldpch.h"
#include "Renderer.h"

#include "imgui_impl_opengl3_loader.h"

namespace Lada::Render {
    Renderer::Renderer(const App::Window& window): m_Window(window) {
    }

    void Renderer::Init() {
        GL_CALL(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
    }

    void Renderer::Shutdown() {
    }

    void Renderer::SubmitMesh(const std::shared_ptr<Mesh>& mesh) {
        m_Meshes.push_back(mesh);
    }

    void Renderer::Draw() const {
        for (const auto& mesh : m_Meshes) {
            mesh->Draw();
        }
    }

    void Renderer::BeginFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::EndFrame() {

    }
}
