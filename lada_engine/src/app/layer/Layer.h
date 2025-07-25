#pragma once
#include <string>

#include "LayerContext.h"
#include "events/Event.h"

namespace Lada::App {
    class Layer {
    public:
        explicit Layer(const std::string& name = "Layer"): m_DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach(LayerContext* context) {}
        virtual void OnDetach(LayerContext* context) {}
        virtual void OnUpdate(LayerContext* context) {}
        virtual void OnRender(LayerContext* context) {}

        virtual void OnEvent(Event::Event& event, LayerContext* context) {}

        [[nodiscard]] const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}
