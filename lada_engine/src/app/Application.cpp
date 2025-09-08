#include "ldpch.h"
#include "Application.h"
#include "GlCall.h"
#include "renderer/Renderer.h"
#include "Logger.h"
#include "events/ApplicationEvent.h"
#include "platform/vulkan/pipeline/VulkanShaderCompiler.h"
#include "renderer/GraphicsApiFactory.h"

namespace Lada::App {
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& title, const int width, const int height): m_Window(nullptr) {
        const GraphicsApiFactory apiFactory(GraphicAPI::VULKAN);
        m_LayerContext = new LayerContext();
        m_LayerStack = new LayerStack(m_LayerContext);
        if (s_Instance != nullptr) {
            LD_CORE_CRITICAL("Application already initialized!");
            return;
        }
        s_Instance = this;
        m_EventManager = std::make_unique<EventManager>();
        m_Window = Window::Create(title, width, height, *m_EventManager, GraphicAPI::VULKAN);
        m_GraphicsContext = apiFactory.CreateContext(*m_Window);
        m_GraphicsContext->Init();
        m_Renderer = std::make_shared<Render::Renderer>(*m_Window, *m_GraphicsContext);
        const VulkanShaderCompiler compiler(true, true);
        auto result = compiler.CompileString(
            R"EoS(#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
})EoS", ShaderStage::Fragment);

        if (apiFactory.GetAPI() ==  GraphicAPI::VULKAN) {
            std::exit(0);
        }

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));

        m_EventManager->BIND_HANDLER(WindowCloseEvent, Application::OnWindowCloseEvent);
        SubscribeLayersOnEvents();

        m_EventManager->BIND_HANDLER(WindowResizeEvent, Application::OnWindowResizeEvent);
    }

    Application::~Application() {
        delete m_LayerStack;
        delete m_LayerContext;
    }

    bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
        this->Shutdown();
        return true;
    }

    bool Application::OnWindowResizeEvent(const WindowResizeEvent &event) {
        glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return true;
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer *layer : *m_LayerStack) {
                layer->OnUpdate(m_LayerContext);
            }
            m_Renderer->BeginFrame();
            for (Layer* layer : *m_LayerStack) {
                layer->OnRender(m_LayerContext, m_Renderer);
            }
            m_Renderer->EndFrame();
            m_Window->OnUpdate();
        }
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

    void Application::SubscribeLayersOnEvents() {
        m_EventManager->RegisterGlobalHandler([this](Event& event) {
            for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
                (*--it)->OnEvent(event, m_LayerContext);
                if (event.IsHandled())
                    break;
            }
            return true;
        });
    }
}
