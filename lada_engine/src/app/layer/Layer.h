#pragma once
#include <string>

#include "events/Event.h"

namespace Lada::App {
    template<typename T>
    class Layer {
    public:
        explicit Layer(const std::string& name = "Layer"): m_DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach(T& context) {}
        virtual void OnDetach(T& context) {}
        virtual void OnUpdate(T& context) {}
        virtual void OnRender(T& context) {}

        virtual void OnEvent(Event::Event& event, T& context) {}

        const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}
