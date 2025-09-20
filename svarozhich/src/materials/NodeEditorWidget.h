#pragma once

#include <QWidget>
#include <memory>
#include <QtNodes/GraphicsView>
#include <QtNodes/BasicGraphicsScene>

#include "ShaderGraphModel.h"
#include "inspector/CameraComponentWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NodeEditorWidget; }
QT_END_NAMESPACE

class NodeEditorWidget final : public QWidget {
    Q_OBJECT
public:
    explicit NodeEditorWidget(QWidget* parent = nullptr);
    ~NodeEditorWidget() override;
    signals:
        void graphChanged(const QString& json);

public slots:
    void newGraph();
    void fitView();
    void zoomIn();
    void zoomOut();

private:
    std::unique_ptr<Ui::NodeEditorWidget> ui;
    std::unique_ptr<QtNodes::BasicGraphicsScene> m_Scene;
    std::unique_ptr<QtNodes::GraphicsView>  m_View;
    std::unique_ptr<ShaderGraphModel> m_Model;

    std::unique_ptr<QAction> createNodeAction;

    void initCreateActions();
    void createNode(QPoint position, const std::shared_ptr<Svch::NodeElement> &nodeModel) const;
};
