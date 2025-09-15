#pragma once

#include <memory>
#include <QWidget>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

namespace Ui {
    class SceneHierarchyWidget;
}

QT_END_NAMESPACE

class QAbstractItemModel;
class QItemSelectionModel;


class SceneHierarchyWidget final : public QWidget {
    Q_OBJECT

public:
    explicit SceneHierarchyWidget(QWidget *parent = nullptr);

    ~SceneHierarchyWidget() override;

    void SetModel(QAbstractItemModel *model);

    [[nodiscard]] QTreeView *TreeView() const; // если нужно прямой доступ

signals:
    void addRootRequested();

    void addChildRequested(const QModelIndex &parent);

    void removeRequested(const QModelIndex &index);

private slots:
    void onSceneTreeContextMenu(const QPoint& pos);

private:
    std::unique_ptr<Ui::SceneHierarchyWidget> ui;

    void configureContextMenu();
};
