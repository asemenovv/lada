#pragma once
#include <vector>

#include "Layer.h"

namespace Lada::App {
    class LayerStack {
    public:
        LayerStack(LayerContext& context);
        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopLayer(const Layer *layer);
        void PopOverlay(const Layer *layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_LayerInsert;
        LayerContext& m_LayerContext;
    };
}
