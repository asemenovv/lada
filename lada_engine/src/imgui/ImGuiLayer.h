#pragma once
#include "imgui.h"
#include "app/layer/Layer.h"
#include "events/ApplicationEvent.h"


namespace Lada::Render {
    template<typename T>
    class ImGuiLayer : public App::Layer<T> {
    public:
        ImGuiLayer();

        void OnAttach(T& context) override;

        void OnDetach(T& context) override;

        void OnUpdate(T& context) override;

        void OnRender(T& context) override;

        void OnEvent(Event::Event &event, T& context) override;

        virtual void RenderElements(const ImGuiIO& io, T& context);
    private:
        void SetDarkThemeColors();
    };
}
