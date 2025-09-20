#pragma once

namespace Svch {
    enum class NodeType {
        INPUT,
        OUTPUT,
        OPERATION,
        NOP
    };

    class NodeElement {
    public:
        NodeElement() = default;

        virtual ~NodeElement() = default;

        virtual NodeType GetNodeType() const { return NodeType::NOP; }

        virtual std::string GetCaption() const;

        virtual unsigned int InputPorts() const {
            return 0;
        }

        virtual unsigned int OutputPorts() const {
            return 0;
        }
    };

    class InputNodeElement final : public NodeElement {
    public:
        explicit InputNodeElement(const std::string &variableName);

        ~InputNodeElement() override = default;

        NodeType GetNodeType() const override;

        std::string GetCaption() const override;

        unsigned int InputPorts() const override;

        unsigned int OutputPorts() const override;
    private:
        std::string m_VariableName;
    };

    class OutputNodeElement final : public NodeElement {
    public:
        OutputNodeElement(const std::string &variableName);

        ~OutputNodeElement() override = default;

        NodeType GetNodeType() const override;

        std::string GetCaption() const override;

        unsigned int InputPorts() const override;

        unsigned int OutputPorts() const override;
    private:
        std::string m_VariableName;
    };

    class BinaryOperationNodeElement final : public NodeElement {
    public:
        BinaryOperationNodeElement() = default;

        ~BinaryOperationNodeElement() override = default;

        NodeType GetNodeType() const override;

        std::string GetCaption() const override;

        unsigned int InputPorts() const override;

        unsigned int OutputPorts() const override;
    };
}
