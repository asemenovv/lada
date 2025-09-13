#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "QDir.h"
#include "QFile.h"
#include "renderer/Camera.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
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

    const auto sceneHierarchyWidget = ui->sceneHierarchy;
    sceneHierarchyWidget->SetModel(m_SceneTreeModel.get());

    connect(sceneHierarchyWidget, &SceneHierarchyWidget::addRootRequested, this, [this]{
        // m_SceneTreeModel->AddEntity("Root", NodeType::MESH);
    });
    connect(sceneHierarchyWidget, &SceneHierarchyWidget::addChildRequested, this, [this](const QModelIndex& p){
        // m_SceneTreeModel->AddChild(p, "Child", NodeType::MESH);
    });
    connect(sceneHierarchyWidget, &SceneHierarchyWidget::removeRequested, this, [this](const QModelIndex& p){
        m_SceneTreeModel->Remove(p);
    });

    qInfo() << "List :/icons =" << QDir(":/icons").entryList();
    // Должен вывести: {"camera.png","mesh.png","directional_light.png","lightbulb.png","spot_light.png"}

    qInfo() << "exists camera =" << QFile(":/icons/camera.png").exists();
    qInfo() << "isNull camera =" << QIcon(":/icons/camera.png").isNull();
}

MainWindow::~MainWindow() = default;

