#include "ldpch.h"
#include "LayerStack.h"

namespace Lada::App {
    LayerStack::LayerStack(LayerContext* context): m_LayerContext(context) {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack() {
        for (const Layer *layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer) {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
        layer->OnAttach(m_LayerContext);
    }

    void LayerStack::PushOverlay(Layer *layer) {
        m_Layers.emplace_back(layer);
        layer->OnAttach(m_LayerContext);
    }

    void LayerStack::PopLayer(const Layer *layer) {
        const auto it = std::ranges::find(m_Layers, layer);
        if (it != m_Layers.end()) {
            (*it)->OnDetach(m_LayerContext);
            m_Layers.erase(it);
            --m_LayerInsert;
        }
    }

    void LayerStack::PopOverlay(const Layer *layer) {
        const auto it = std::ranges::find(m_Layers, layer);
        if (it != m_Layers.end()) {
            (*it)->OnDetach(m_LayerContext);
            m_Layers.erase(it);
        }
    }
}
