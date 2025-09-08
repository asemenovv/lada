#pragma once
#include "imgui.h"
#include "app/layer/Layer.h"
#include "events/ApplicationEvent.h"


namespace Lada::Render {
    class ImGuiLayer : public App::Layer {
    public:
        ImGuiLayer();

        void OnAttach(App::LayerContext& context) override;

        void OnDetach(App::LayerContext& context) override;

        void OnUpdate(App::LayerContext& context) override;

        void OnRender(App::LayerContext& context, const std::shared_ptr<Renderer> &renderer) override;

        void OnEvent(Event &event, App::LayerContext& context) override;

        virtual void RenderElements(const ImGuiIO& io, App::LayerContext& context);
    private:
        void SetDarkThemeColors();
    };
}
