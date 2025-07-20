#pragma once

#include <unordered_map>

namespace Lada::App {
    class LayerContext {
    public:
        float* GetF(const std::string& name);
        void SetF(const std::string& name, float value);
    private:
        std::unordered_map<std::string, float> m_FloatVariables;
    };
}
