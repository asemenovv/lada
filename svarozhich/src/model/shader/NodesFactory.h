#pragma once

#include <string>

#include "NodeElement.h"

namespace Svch {
    class NodesFactory {
    public:
        static std::shared_ptr<InputNodeElement> ScalarProperty(const std::string &variableName);

        static std::shared_ptr<InputNodeElement> ColorRGBProperty(const std::string &variableName);

        static std::shared_ptr<InputNodeElement> ColorRGBAProperty(const std::string &variableName);

        static std::shared_ptr<OutputNodeElement> OutputColor();
    };
}
