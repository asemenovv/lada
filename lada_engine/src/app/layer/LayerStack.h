#pragma once
#include <vector>

#include "Layer.h"

namespace Lada::App {
    template<typename T>
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer<T> *layer);
        void PushOverlay(Layer<T> *layer);
        void PopLayer(const Layer<T> *layer);
        void PopOverlay(const Layer<T> *layer);

        std::vector<Layer<T>*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer<T>*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer<T>*> m_Layers;
        std::vector<Layer<T>*>::iterator m_LayerInsert;
    };
}
