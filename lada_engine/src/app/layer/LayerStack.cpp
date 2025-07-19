#include "ldpch.h"
#include "LayerStack.h"

namespace Lada::App {
    template<typename T>
    LayerStack<T>::LayerStack() {
        m_LayerInsert = m_Layers.begin();
    }

    template<typename T>
    LayerStack<T>::~LayerStack() {
        for (const Layer<T> *layer : m_Layers) {
            delete layer;
        }
    }

    template<typename T>
    void LayerStack<T>::PushLayer(Layer<T> *layer) {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
        layer->OnAttach();
    }

    template<typename T>
    void LayerStack<T>::PushOverlay(Layer<T> *layer) {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    template<typename T>
    void LayerStack<T>::PopLayer(const Layer<T> *layer) {
        const auto it = std::ranges::find(m_Layers, layer);
        if (it != m_Layers.end()) {
            (*it)->OnDetach();
            m_Layers.erase(it);
            --m_LayerInsert;
        }
    }

    template<typename T>
    void LayerStack<T>::PopOverlay(const Layer<T> *layer) {
        const auto it = std::ranges::find(m_Layers, layer);
        if (it != m_Layers.end()) {
            (*it)->OnDetach();
            m_Layers.erase(it);
        }
    }
}
