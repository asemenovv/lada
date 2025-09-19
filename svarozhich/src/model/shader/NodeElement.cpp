#include "NodeElement.h"

namespace Svch {
    std::string NodeElement::GetCaption() const {
        return "IN vec3";
    }

    NodeType InputNodeElement::GetNodeType() const {
        return NodeType::INPUT;
    }

    std::string InputNodeElement::GetCaption() const {
        return "IN";
    }

    unsigned int InputNodeElement::InputPorts() const {
        return 0;
    }

    unsigned int InputNodeElement::OutputPorts() const {
        return 1;
    }

    NodeType OutputNodeElement::GetNodeType() const {
        return NodeType::OUTPUT;
    }

    std::string OutputNodeElement::GetCaption() const {
        return "OUT";
    }

    unsigned int OutputNodeElement::InputPorts() const {
        return 1;
    }

    unsigned int OutputNodeElement::OutputPorts() const {
        return 0;
    }

    NodeType BinaryOperationNodeElement::GetNodeType() const {
        return NodeType::OPERATION;
    }

    std::string BinaryOperationNodeElement::GetCaption() const {
        return "a * b";
    }

    unsigned int BinaryOperationNodeElement::InputPorts() const {
        return 2;
    }

    unsigned int BinaryOperationNodeElement::OutputPorts() const {
        return 1;
    }
} // Svch