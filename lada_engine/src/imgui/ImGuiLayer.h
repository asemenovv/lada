#pragma once
#include "imgui.h"
#include "app/layer/Layer.h"
#include "events/ApplicationEvent.h"


namespace Lada::Render {
    class ImGuiLayer : public App::Layer {
    public:
        ImGuiLayer();

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate() override;

        void OnRender() override;

        void OnEvent(Event::Event &event) override;

        virtual void RenderElements(const ImGuiIO& io);
    private:
        void SetDarkThemeColors();
    };
}
