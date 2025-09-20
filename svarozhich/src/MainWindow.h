#pragma once

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <memory>

#include "inspector/InspectorWidget.h"
#include "materials/NodeEditorWidget.h"
#include "scene/SceneHierarchyWidget.h"
#include "scene/SceneTreeModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public KDDockWidgets::QtWidgets::MainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<SceneTreeModel> m_SceneTreeModel;
    std::vector<Svch::Entity> m_Entities;

    KDDockWidgets::QtWidgets::DockWidget* m_DockSceneHierarchy;
    SceneHierarchyWidget* m_SceneHierarchy;

    KDDockWidgets::QtWidgets::DockWidget* m_DockInspector;
    InspectorWidget* m_Inspector;

    KDDockWidgets::QtWidgets::DockWidget* m_DockNodeEditor;
    NodeEditorWidget* m_NodeEditor;
};
