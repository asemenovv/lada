#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "renderer/Camera.h"

MainWindow::MainWindow(QWidget *parent): KDDockWidgets::QtWidgets::MainWindow("Svarožič", {}, parent),
                                         ui(std::make_unique<Ui::MainWindow>()) {

    ui->setupUi(this);

    m_SceneTreeModel = std::make_unique<SceneTreeModel>();
    m_Entities.emplace_back("Camera");
    m_Entities.emplace_back("Sun Directional Light",
        std::vector<std::string>{"Global", "Rendering", "Lights"});
    m_Entities.emplace_back("Floor", std::vector<std::string>{"Room"});
    m_Entities.emplace_back("Vase", std::vector<std::string>{"Room"});
    m_Entities.emplace_back("Table", std::vector<std::string>{"Room"});
    for (auto& entity : m_Entities) {
        m_SceneTreeModel->AddEntity(&entity);
    }

    m_DockNodeEditor = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Shader Material"));
    m_NodeEditor = new NodeEditorWidget();
    m_DockNodeEditor->setWidget(m_NodeEditor);
    addDockWidget(m_DockNodeEditor, KDDockWidgets::Location_OnTop);

    m_SceneHierarchy = new SceneHierarchyWidget();
    m_SceneHierarchy->SetModel(m_SceneTreeModel.get());
    auto* sceneHierarchyScrollArea = new QScrollArea();
    sceneHierarchyScrollArea->setWidgetResizable(true);
    sceneHierarchyScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneHierarchyScrollArea->setFrameShape(QFrame::NoFrame);
    sceneHierarchyScrollArea->setWidget(m_SceneHierarchy);
    sceneHierarchyScrollArea->setMinimumWidth(300);
    sceneHierarchyScrollArea->setFixedWidth(300);
    sceneHierarchyScrollArea->setMaximumWidth(370);
    sceneHierarchyScrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_DockSceneHierarchy = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Scene Hierarchy"));
    m_DockSceneHierarchy->setWidget(sceneHierarchyScrollArea);
    addDockWidget(m_DockSceneHierarchy, KDDockWidgets::Location_OnLeft);

    m_Inspector = new InspectorWidget();
    auto* inspectorScrollArea = new QScrollArea();
    inspectorScrollArea->setWidgetResizable(true);
    inspectorScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    inspectorScrollArea->setFrameShape(QFrame::NoFrame);
    inspectorScrollArea->setWidget(m_Inspector);
    inspectorScrollArea->setMinimumWidth(370);
    inspectorScrollArea->setMaximumWidth(370);
    inspectorScrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_DockInspector = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Inspector"));
    m_DockInspector->setWidget(inspectorScrollArea);
    addDockWidget(m_DockInspector, KDDockWidgets::Location_OnRight);

    // connect(sceneHierarchyWidget, &SceneHierarchyWidget::addRootRequested, this, [this]{
    //     // m_SceneTreeModel->AddEntity("Root", NodeType::MESH);
    // });
    // connect(sceneHierarchyWidget, &SceneHierarchyWidget::addChildRequested, this, [this](const QModelIndex& p){
    //     // m_SceneTreeModel->AddChild(p, "Child", NodeType::MESH);
    // });
    // connect(sceneHierarchyWidget, &SceneHierarchyWidget::removeRequested, this, [this](const QModelIndex& p){
    //     m_SceneTreeModel->Remove(p);
    // });
}

MainWindow::~MainWindow() = default;

