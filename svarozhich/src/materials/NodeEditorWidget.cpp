#include "NodeEditorWidget.h"

#include <qinputdialog.h>

#include "ShaderGraphModel.h"
#include "ui_nodeeditorwidget.h"
#include "model/shader/NodesFactory.h"

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

    const QtNodes::NodeId outColor = m_Model->addNode();
    m_Model->setNodeData(outColor, QtNodes::NodeRole::Position, QPointF(300, 0));
    m_Model->SetNodeModel(outColor, Svch::NodesFactory::OutputColor());

    m_Scene = std::make_unique<QtNodes::BasicGraphicsScene>(*m_Model);
    m_View = std::make_unique<QtNodes::GraphicsView>(m_Scene.get());
    m_View->setContextMenuPolicy(Qt::ActionsContextMenu);

    initCreateActions();

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

void NodeEditorWidget::initCreateActions() {
    createNodeAction = std::make_unique<QAction>(QStringLiteral("Create Node"), m_View.get());

    auto* menuCreate = new QMenu(tr("Create"), this);
    createNodeAction->setMenu(menuCreate);

    auto* createInput = new QMenu(tr("Input"), this);
    createInput->addAction(QStringLiteral("Scalar"), this, [&]() {
        const QString name = QInputDialog::getText(this,QStringLiteral("Enter Property Name"),
            QStringLiteral("Name:"), QLineEdit::Normal, "");
        createNode(QCursor::pos(), Svch::NodesFactory::ScalarProperty(name.toStdString()));
    });
    createInput->addAction(QStringLiteral("Color RGB"), this, [&]() {
        const QString name = QInputDialog::getText(this,QStringLiteral("Enter Property Name"),
            QStringLiteral("Name:"), QLineEdit::Normal, "");
        createNode(QCursor::pos(), Svch::NodesFactory::ColorRGBProperty(name.toStdString()));
    });
    createInput->addAction(QStringLiteral("Color RGBA"), this, [&]() {
        const QString name = QInputDialog::getText(this,QStringLiteral("Enter Property Name"),
            QStringLiteral("Name:"), QLineEdit::Normal, "");
        createNode(QCursor::pos(), Svch::NodesFactory::ColorRGBAProperty(name.toStdString()));
    });
    menuCreate->addMenu(createInput);

    auto* createArithmetic = new QMenu(tr("Arithmetic"), this);
    createArithmetic->addAction(QStringLiteral("Addition +"), this, [&]() {});
    createArithmetic->addAction(QStringLiteral("Substraction -"), this, [&]() {});
    createArithmetic->addAction(QStringLiteral("Multiplication *"), this, [&]() {});
    createArithmetic->addAction(QStringLiteral("Division /"), this, [&]() {});
    menuCreate->addMenu(createArithmetic);

    auto* createOutput = new QMenu(tr("Output"), this);
    createOutput->addAction(QStringLiteral("Fragment Color"), this, [&]() {});
    menuCreate->addMenu(createOutput);

    connect(createNodeAction.get(), &QAction::triggered, [&]() {
        const QPointF posView = m_View->mapToScene(m_View->mapFromGlobal(QCursor::pos()));
        QtNodes::NodeId const newId = m_Model->addNode();
        m_Model->setNodeData(newId, QtNodes::NodeRole::Position, posView);
        m_Model->SetNodeModel(newId, std::make_shared<Svch::BinaryOperationNodeElement>());
    });
    m_View->insertAction(m_View->actions().front(), createNodeAction.get());
}

void NodeEditorWidget::createNode(const QPoint position, const std::shared_ptr<Svch::NodeElement> &nodeModel) const {
    const QPointF posView = m_View->mapToScene(m_View->mapFromGlobal(position));
    QtNodes::NodeId const newId = m_Model->addNode();
    m_Model->setNodeData(newId, QtNodes::NodeRole::Position, posView);
    m_Model->SetNodeModel(newId, nodeModel);

}
