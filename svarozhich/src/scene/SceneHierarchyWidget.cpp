#include "SceneHierarchyWidget.h"

#include "ui_scenehierarchywidget.h"

SceneHierarchyWidget::SceneHierarchyWidget(QWidget *parent) : QWidget(parent),
                                                              ui(std::make_unique<Ui::SceneHierarchyWidget>()) {
    ui->setupUi(this);

    ui->btnAddChild->setEnabled(false);
    ui->btnRemove->setEnabled(false);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this] {
        const bool hasSel = ui->treeView->selectionModel()->hasSelection();
        ui->btnAddChild->setEnabled(hasSel);
        ui->btnRemove->setEnabled(hasSel);
    });

    connect(ui->btnAddRoot, &QPushButton::clicked, this, [this] {
        emit addRootRequested();
    });
    connect(ui->btnAddChild, &QPushButton::clicked, this, [this] {
        const auto sel = ui->treeView->selectionModel();
        emit addChildRequested(sel ? sel->currentIndex() : QModelIndex{});
    });
    connect(ui->btnRemove, &QPushButton::clicked, this, [this] {
        const auto sel = ui->treeView->selectionModel();
        emit removeRequested(sel ? sel->currentIndex() : QModelIndex{});
    });
}

SceneHierarchyWidget::~SceneHierarchyWidget() = default;

void SceneHierarchyWidget::SetModel(QAbstractItemModel *model) {
    ui->treeView->setModel(model);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this] {
                const bool hasSel = ui->treeView->selectionModel()->hasSelection();
                ui->btnAddChild->setEnabled(hasSel);
                ui->btnRemove->setEnabled(hasSel);
            });
}

QTreeView *SceneHierarchyWidget::TreeView() const {
    return ui->treeView;
}
