#include "ldpch.h"
#include "Application.h"
#include "renderer/Renderer.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"
#include "platform/vulkan/pipeline/VulkanShaderCompiler.h"
#include "renderer/GraphicsApiFactory.h"
#include "scene/Components.h"
#include "scene/Entity.h"

namespace Lada::App {
    Application *Application::s_Instance = nullptr;

    Application::Application(const std::string &title, const int width, const int height) : m_Window(nullptr) {
        const GraphicsApiFactory apiFactory(GraphicAPI::VULKAN);
        m_LayerContext = std::make_unique<LayerContext>();
        m_LayerStack = std::make_unique<LayerStack>(*m_LayerContext);
        if (s_Instance != nullptr) {
            LD_CORE_CRITICAL("Application already initialized!");
            return;
        }
        s_Instance = this;
        m_EventManager = std::make_unique<EventManager>();
        m_Window = Window::Create(title, width, height, *m_EventManager, GraphicAPI::VULKAN);
        m_GraphicsContext = apiFactory.CreateContext(*m_Window);
        m_Scene = std::make_unique<Scene>(m_GraphicsContext.get());
        m_AssetManager = std::make_unique<AssetManager>(m_GraphicsContext.get());
        m_GraphicsContext->Init();
        loadScene();

        m_Renderer = std::make_unique<Render::Renderer>(*m_Window, m_GraphicsContext.get(), m_EventManager.get());
        m_SceneRenderer  = std::make_unique<SceneRenderer>(m_Scene.get(), m_Renderer.get(), m_AssetManager.get());
        LD_CORE_INFO("Application initialized");


        /*const VulkanShaderCompiler compiler(true, true);
        auto result = compiler.CompileString(
            R"EoS(#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
})EoS", ShaderStage::Fragment);*/

        // if (apiFactory.GetAPI() == GraphicAPI::VULKAN) {
            // std::exit(0);
        // }

        m_EventManager->BIND_HANDLER(WindowCloseEvent, Application::onWindowCloseEvent);
        subscribeLayersOnEvents();
    }

    bool Application::onWindowCloseEvent(const WindowCloseEvent &event) {
        this->Shutdown();
        return true;
    }

    void Application::loadScene() {
        auto camera = m_Scene->CreateEntity();
        camera.AddComponent<IdComponent>(UUID());
        camera.AddComponent<NameComponent>("Camera");
        camera.AddComponent<CameraComponent>(CameraComponent{
            .Type = CameraType::Perspective,
            .FOVDegrees = 50.0f,
            .AutoAspectRatio = true,
            .NearPlane = 0.1f,
            .FarPlane = 10.0f,
        });
        camera.AddComponent<TransformComponent>(
            glm::vec3{-1.5f, 0.1f, 0.0f},
            glm::quat{1.0f, 0.0f, 0.0f, 0.0},
            glm::vec3{1.0f, 1.0f, 1.0f}
        );

        auto smoothVaseId = m_AssetManager->Register(AssetType::Mesh,
        "/Users/alexeysemenov/CLionProjects/lada/assets/models/smooth_vase.obj");
        auto smoothVase = m_Scene->CreateEntity();
        smoothVase.AddComponent<IdComponent>(UUID());
        smoothVase.AddComponent<NameComponent>("Smooth Vase");
        smoothVase.AddComponent<FolderComponent>(std::vector<std::string>{"Room"});
        smoothVase.AddComponent<TransformComponent>(
            glm::vec3{0.0, 0.0, 0.5},
            glm::quat{180.0f, 1.0f, 0.0f, 0.0},
            glm::vec3{2.0f, 1.0f, 2.0f}
        );
        smoothVase.AddComponent<MeshComponent>(smoothVaseId);

        auto flatVaseId = m_AssetManager->Register(AssetType::Mesh,
        "/Users/alexeysemenov/CLionProjects/lada/assets/models/flat_vase.obj");
        auto flatVase = m_Scene->CreateEntity();
        flatVase.AddComponent<IdComponent>(UUID());
        flatVase.AddComponent<NameComponent>("Smooth Vase");
        flatVase.AddComponent<FolderComponent>(std::vector<std::string>{"Room"});
        flatVase.AddComponent<TransformComponent>(
            glm::vec3{0.0, 0.0, -0.5},
            glm::quat{180.0f, 1.0f, 0.0f, 0.0},
            glm::vec3{2.0f, 1.0f, 2.0f}
        );
        flatVase.AddComponent<MeshComponent>(flatVaseId);

        auto floorId = m_AssetManager->Register(AssetType::Mesh,
        "/Users/alexeysemenov/CLionProjects/lada/assets/models/quad.obj");
        auto floor = m_Scene->CreateEntity();
        floor.AddComponent<IdComponent>(UUID());
        floor.AddComponent<NameComponent>("Floor");
        floor.AddComponent<FolderComponent>(std::vector<std::string>{"Room"});
        floor.AddComponent<TransformComponent>(
            glm::vec3{0.0},
            glm::quat{180.0f, 1.0f, 0.0f, 0.0},
            glm::vec3{3.0f, 1.0f, 3.0f}
        );
        floor.AddComponent<MeshComponent>(floorId);

        auto triangleId = m_AssetManager->Register(AssetType::Mesh,
        "/Users/alexeysemenov/CLionProjects/lada/assets/models/triangle.obj");
        auto triangle = m_Scene->CreateEntity();
        triangle.AddComponent<IdComponent>(UUID());
        triangle.AddComponent<NameComponent>("Triangle");
        triangle.AddComponent<FolderComponent>(std::vector<std::string>{"Room"});
        triangle.AddComponent<TransformComponent>(
            glm::vec3{0.0},
            glm::quat{0.0f, 0.0f, 0.0f, 0.0},
            glm::vec3{1.0f}
        );
        triangle.AddComponent<MeshComponent>(triangleId);
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer *layer: *m_LayerStack) {
                layer->OnUpdate(*m_LayerContext);
            }
            m_SceneRenderer->DrawScene();
            // m_Renderer->BeginFrame();
            // m_Renderer->Submit(nullptr);
            // for (Layer *layer: *m_LayerStack) {
            //     layer->OnRender(*m_LayerContext, *m_Renderer);
            // }
            // m_Renderer->EndFrame();
            m_Window->OnUpdate();
        }
        m_GraphicsContext->WaitIdle();
    }

    void Application::Shutdown() {
        m_Window->Close();
        m_Running = false;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack->PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack->PushOverlay(layer);
    }

    void Application::PopLayer(const Layer *layer) {
        m_LayerStack->PopLayer(layer);
    }

    void Application::PopOverlay(Layer *layer) {
        m_LayerStack->PopOverlay(layer);
    }

    void Application::subscribeLayersOnEvents() {
        m_EventManager->RegisterGlobalHandler([this](Event &event) {
            for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
                (*--it)->OnEvent(event, *m_LayerContext);
                if (event.IsHandled())
                    break;
            }
            return true;
        });
    }
}
