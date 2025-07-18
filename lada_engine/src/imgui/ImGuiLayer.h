#pragma once
#include "app/layer/Layer.h"


namespace Lada::Render {
    class ImGuiLayer final : public App::Layer {
    public:
        ImGuiLayer();

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate() override;

        void OnRender() override;

        void OnEvent(const Event::Event &event) override;
    private:
        void SetDarkThemeColors();
    };
}
