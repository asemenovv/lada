#pragma once

#include <QAbstractItemModel>

#include "model/Entity.h"

enum class NodeType {
    ENTITY = 0,
    FOLDER = 1,
    ROOT = 5,
};

struct TreeItem {
    Svch::Entity* entity;
    std::string name;
    NodeType type;
    TreeItem* parent = nullptr;
    std::vector<std::unique_ptr<TreeItem>> children;

    explicit TreeItem(Svch::Entity* ent, NodeType type, TreeItem* parent=nullptr);

    explicit TreeItem(std::string name_, NodeType type, TreeItem* parent=nullptr);

    int row() const;

    int childCount() const;

    TreeItem* child(int r) const;

    TreeItem* AppendFolder(std::string folderName);

    TreeItem *AppendEntity(Svch::Entity* entity);

    int indexOf(TreeItem* item);
};

class SceneTreeModel final : public QAbstractItemModel {
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1
    };

    explicit SceneTreeModel(QObject* parent=nullptr);

    QModelIndex index(int row, int column, const QModelIndex& parent) const override;

    QModelIndex parent(const QModelIndex& idx) const override;

    int rowCount(const QModelIndex& parent) const override;

    int columnCount(const QModelIndex&) const override;

    QVariant data(const QModelIndex& idx, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& idx) const override;

    auto roleNames() const -> QHash<int, QByteArray> override;

    // bool setData(const QModelIndex& idx, const QVariant& value, int role) override;

    void AddEntity(Svch::Entity* entity);

    void AddChild(const QModelIndex& parentIndex, const QString& name, NodeType type);

    void Remove(const QModelIndex& index);

private:
    std::unique_ptr<TreeItem> m_Root;
    std::unordered_map<std::string, TreeItem*> m_FoldersCache;

    TreeItem* addFolderIfNotExist(TreeItem* parent, std::vector<std::string> pathElements);
    QModelIndex indexFromItem(TreeItem* item, int column) const;
};
