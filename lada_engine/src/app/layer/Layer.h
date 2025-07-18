#pragma once
#include <string>

#include "events/Event.h"

namespace Lada::App {
    class Layer {
    public:
        explicit Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnRender() {}

        virtual void OnEvent(const Event::Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}
