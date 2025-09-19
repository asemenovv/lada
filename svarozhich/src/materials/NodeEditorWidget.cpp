#include "NodeEditorWidget.h"

#include "ShaderGraphModel.h"
#include "ui_nodeeditorwidget.h"

namespace DemoNodes {
    // forward declare, чтобы не тянуть реальную имплементацию сюда
    std::unique_ptr<ShaderGraphModel> makeConstantColorModel();
    std::unique_ptr<ShaderGraphModel> makeMultiplyModel();
    std::unique_ptr<ShaderGraphModel> makeOutputModel();
}

NodeEditorWidget::NodeEditorWidget(QWidget *parent)
        : QWidget(parent), ui(std::make_unique<Ui::NodeEditorWidget>()) {
    ui->setupUi(this);
    m_Model = std::make_unique<ShaderGraphModel>();

    {
        for (int i = 0; i < 3; i++) {
            const QtNodes::NodeId inColor = m_Model->addNode();
            m_Model->setNodeData(inColor, QtNodes::NodeRole::Position, QPointF(0, i * 120));
            m_Model->SetNodeModel(inColor, new Svch::InputNodeElement());
        }
        const QtNodes::NodeId outColor = m_Model->addNode();
        m_Model->setNodeData(outColor, QtNodes::NodeRole::Position, QPointF(300, 0));
        m_Model->SetNodeModel(outColor, new Svch::OutputNodeElement());

        const QtNodes::NodeId mul = m_Model->addNode();
        m_Model->setNodeData(mul, QtNodes::NodeRole::Position, QPointF(150, 0));
        m_Model->SetNodeModel(mul, new Svch::BinaryOperationNodeElement());
        // m_Model->addConnection(QtNodes::ConnectionId{id1, 0, id2, 0});
    }

    m_Scene = std::make_unique<QtNodes::BasicGraphicsScene>(*m_Model);
    m_View = std::make_unique<QtNodes::GraphicsView>(m_Scene.get());
    m_View->setContextMenuPolicy(Qt::ActionsContextMenu);

    createNodeAction = std::make_unique<QAction>(QStringLiteral("Create Node"), m_View.get());
    connect(createNodeAction.get(), &QAction::triggered, [&]() {
        const QPointF posView = m_View->mapToScene(m_View->mapFromGlobal(QCursor::pos()));
        QtNodes::NodeId const newId = m_Model->addNode();
        m_Model->setNodeData(newId, QtNodes::NodeRole::Position, posView);
        m_Model->SetNodeModel(newId, new Svch::BinaryOperationNodeElement());
    });
    m_View->insertAction(m_View->actions().front(), createNodeAction.get());

    // m_View->setWindowTitle("Simple Node Graph");
    m_View->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->viewLayout->addWidget(m_View.get());
}

NodeEditorWidget::~NodeEditorWidget() = default;

void NodeEditorWidget::newGraph() {
}

void NodeEditorWidget::fitView() {
}

void NodeEditorWidget::zoomIn() {
}

void NodeEditorWidget::zoomOut() {
}

void NodeEditorWidget::connectUi() {
}

void NodeEditorWidget::buildRegistry() {
}
