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
    private:
        unsigned int m_InPorts;
        unsigned int m_OutPorts;
    };

    class InputNodeElement final : public NodeElement {
    public:
        InputNodeElement() = default;

        ~InputNodeElement() override = default;

        NodeType GetNodeType() const override;

        std::string GetCaption() const override;

        unsigned int InputPorts() const override;

        unsigned int OutputPorts() const override;
    };

    class OutputNodeElement final : public NodeElement {
    public:
        OutputNodeElement() = default;

        ~OutputNodeElement() override = default;

        NodeType GetNodeType() const override;

        std::string GetCaption() const override;

        unsigned int InputPorts() const override;

        unsigned int OutputPorts() const override;
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
