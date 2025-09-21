#include "SceneHierarchyWidget.h"

#include <qmenu.h>

#include "SceneTreeModel.h"
#include "ui_scenehierarchywidget.h"

SceneHierarchyWidget::SceneHierarchyWidget(QWidget *parent) : QWidget(parent),
                                                              ui(std::make_unique<Ui::SceneHierarchyWidget>()) {
    ui->setupUi(this);

    m_SceneTreeModel = std::make_unique<SceneTreeModel>();
    ui->treeView->setModel(m_SceneTreeModel.get());

    configureContextMenu();

    // connect(ui->btnAddRoot, &QPushButton::clicked, this, [this] {
        // emit addRootRequested();
    // });
    // connect(ui->btnAddChild, &QPushButton::clicked, this, [this] {
        // const auto sel = ui->treeView->selectionModel();
        // emit addChildRequested(sel ? sel->currentIndex() : QModelIndex{});
    // });
    // connect(ui->btnRemove, &QPushButton::clicked, this, [this] {
        // const auto sel = ui->treeView->selectionModel();
        // emit removeRequested(sel ? sel->currentIndex() : QModelIndex{});
    // });
}

SceneHierarchyWidget::~SceneHierarchyWidget() = default;

QTreeView *SceneHierarchyWidget::TreeView() const {
    return ui->treeView;
}

void SceneHierarchyWidget::onSceneTreeContextMenu(const QPoint &pos) {
    QTreeView* tv = ui->treeView;
    QModelIndex idx = tv->indexAt(pos);
    const QPoint globalPos = tv->viewport()->mapToGlobal(pos);
    QMenu menu(this);

    const auto model = dynamic_cast<SceneTreeModel*>(tv->model());
    const TreeItem* item = model->FindItem(idx);
    if (idx.isValid() && item->type == NodeType::FOLDER) {
        tv->selectionModel()->setCurrentIndex(idx, QItemSelectionModel::NoUpdate);

        menu.addAction(QIcon(":/icons/mesh"), tr("Create Entity"), [this, idx, model]{
            // model->AddEntity(idx, "Child");
        });
        menu.addAction(tr("Rename"), [this, idx]{
            // ui->sceneTreeView->edit(idx);
        });
        menu.addSeparator();
        menu.addAction(QIcon(":/icons/spot_light"), tr("Delete"), [idx, model]{
            model->Remove(idx);
        });
    } else {
        menu.addAction(QIcon(":/icons/mesh"), tr("Create Entity"), [this, idx, model]{
            // model->AddEntity(idx, "Child");
        });
        menu.addSeparator();
        menu.addAction(tr("Expand All"), [this]{ ui->treeView->expandAll(); });
        menu.addAction(tr("Collapse All"), [this]{ ui->treeView->collapseAll(); });
    }
    menu.exec(globalPos);
}

void SceneHierarchyWidget::configureContextMenu() {
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QWidget::customContextMenuRequested,
        this, &SceneHierarchyWidget::onSceneTreeContextMenu);
}
