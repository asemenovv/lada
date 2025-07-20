#include "LayerContext.h"

namespace Lada::App {
    float* LayerContext::GetF(const std::string& name) {
        return &m_FloatVariables[name];
    }

    void LayerContext::SetF(const std::string& name, const float value) {
        m_FloatVariables[name] = value;
    }
}
