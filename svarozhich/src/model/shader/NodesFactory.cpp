#include "NodesFactory.h"

namespace Svch {
    std::shared_ptr<InputNodeElement> NodesFactory::ScalarProperty(const std::string &variableName) {
        return std::make_shared<InputNodeElement>(variableName);
    }

    std::shared_ptr<InputNodeElement> NodesFactory::ColorRGBProperty(const std::string &variableName) {
        return std::make_shared<InputNodeElement>(variableName);
    }

    std::shared_ptr<InputNodeElement> NodesFactory::ColorRGBAProperty(const std::string &variableName) {
        return std::make_shared<InputNodeElement>(variableName);
    }

    std::shared_ptr<OutputNodeElement> NodesFactory::OutputColor() {
        return std::make_shared<OutputNodeElement>("Fragment Color");
    }
}
