#include "SceneTreeModel.h"

#include <qicon.h>
#include <utility>
#include <vector>
#include <string>
#include <ranges>

#include "utils.h"
#include "model/Entity.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/fmt/bundled/xchar.h"

TreeItem::TreeItem(Svch::Entity* ent, const NodeType type, TreeItem *parent)
    : entity(ent), type(type), parent(parent) {
}

TreeItem::TreeItem(std::string name_, const NodeType type, TreeItem *parent)
    : entity(nullptr), name(std::move(name_)), type(type), parent(parent) {
}

int TreeItem::row() const {
    if (!parent) return 0;
    for (int i = 0; i < static_cast<int>(parent->children.size()); ++i)
        if (parent->children[i].get() == this) return i;
    return 0;
}

int TreeItem::childCount() const {
    return static_cast<int>(children.size());
}

TreeItem *TreeItem::child(const int r) const {
    return (r >= 0 && r < childCount()) ? children[r].get() : nullptr;
}

TreeItem *TreeItem::AppendFolder(std::string folderName) {
    children.push_back(std::make_unique<TreeItem>(folderName, NodeType::FOLDER, this));
    return children.back().get();
}

TreeItem *TreeItem::AppendEntity(Svch::Entity* entity) {
    children.push_back(std::make_unique<TreeItem>(entity, NodeType::ENTITY, this));
    return children.back().get();
}

int TreeItem::indexOf(TreeItem *item) {
    const auto it = std::ranges::find_if(children,
        [=](auto& ptr){ return ptr.get() == item; });
    if (it != children.end()) {
        return std::distance(children.begin(), it); // idx = 2
    }
    return -1;
}

SceneTreeModel::SceneTreeModel(QObject *parent)
    : QAbstractItemModel(parent),
      m_Root(std::make_unique<TreeItem>(nullptr, NodeType::ROOT, nullptr)) {
}

QModelIndex SceneTreeModel::index(const int row, const int column, const QModelIndex &parent) const {
    if (column != 0 || row < 0) return {};
    const TreeItem *parentItem = parent.isValid()
                                     ? static_cast<TreeItem *>(parent.internalPointer())
                                     : m_Root.get();
    const TreeItem *child = parentItem->child(row);
    return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex SceneTreeModel::indexFromItem(TreeItem* item, const int column) const {
    if (!item || item == m_Root.get())
        return QModelIndex();

    TreeItem* parentItem = item->parent;
    if (!parentItem)
        return QModelIndex();

    int row = parentItem->indexOf(item); // например, найти в QVector
    return createIndex(row, column, item);
}

QModelIndex SceneTreeModel::parent(const QModelIndex &idx) const {
    if (!idx.isValid()) return {};
    const TreeItem *item = static_cast<TreeItem *>(idx.internalPointer());
    const TreeItem *parent = item->parent;
    if (!parent || parent == m_Root.get()) return {};
    return createIndex(parent->row(), 0, parent);
}

int SceneTreeModel::rowCount(const QModelIndex &parent) const {
    const TreeItem *parentItem = parent.isValid()
                                     ? static_cast<TreeItem *>(parent.internalPointer())
                                     : m_Root.get();
    return parentItem->childCount();
}

int SceneTreeModel::columnCount(const QModelIndex &) const {
    return 1;
}

QVariant SceneTreeModel::data(const QModelIndex &idx, const int role) const {
    if (!idx.isValid()) return {};
    const auto item = FindItem(idx);
    if (role == Qt::DisplayRole || role == NameRole) {
        switch (item->type) {
            case NodeType::FOLDER:
                return QString(item->name.c_str());
            case NodeType::ENTITY:
                return QString(item->entity->GetName().c_str());
            default:
                return {};
        }
    }
    if (role == Qt::DecorationRole) {
        switch (item->type) {
            case NodeType::FOLDER:
                return QIcon(":/icons/folder_open_24");
            case NodeType::ENTITY:
                return QIcon(":/icons/mesh");
            default:
                return {};
        }
    }
    return {};
}

Qt::ItemFlags SceneTreeModel::flags(const QModelIndex &idx) const {
    if (!idx.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QHash<int, QByteArray> SceneTreeModel::roleNames() const {
    return {{NameRole, "name"}};
}

/*bool SceneTreeModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
    if (!idx.isValid()) return false;
    if (role == Qt::EditRole || role == NameRole) {
        auto *item = static_cast<TreeItem *>(idx.internalPointer());
        // item->name = value.toString(); TODO: Update
        emit dataChanged(idx, idx, {role, Qt::DisplayRole});
        return true;
    }
    return false;
}*/

void SceneTreeModel::AddEntity(Svch::Entity* entity) {
    const auto paths = Svch::prefixes(entity->GetFolderPath());
    TreeItem* parent = m_Root.get();
    for (auto& path : paths) {
        parent = addFolderIfNotExist(parent, path);
    }
    const int r = parent->childCount();
    const auto parentIndex = indexFromItem(parent, 0);
    beginInsertRows(parentIndex, r, r);
    parent->AppendEntity(entity);
    endInsertRows();
}

/*void SceneTreeModel::AddChild(const QModelIndex &parentIndex, const QString &name, NodeType type) {
    TreeItem *parentItem = parentIndex.isValid()
                               ? static_cast<TreeItem *>(parentIndex.internalPointer())
                               : m_Root.get();
    const int r = parentItem->childCount();
    beginInsertRows(parentIndex, r, r);
    parentItem->append(name, type);
    endInsertRows();
}*/

void SceneTreeModel::Remove(const QModelIndex &index) {
    if (!index.isValid()) return;
    const auto *item = FindItem(index);
    TreeItem *parent = item->parent;
    if (!parent) return;
    const int row = item->row();
    beginRemoveRows(index.parent(), row, row);
    parent->children.erase(parent->children.begin() + row);
    endRemoveRows();
}

TreeItem* SceneTreeModel::FindItem(const QModelIndex &index) const {
    if (!index.isValid()) return nullptr;
    return static_cast<TreeItem *>(index.internalPointer());
}

TreeItem* SceneTreeModel::addFolderIfNotExist(TreeItem* parent, std::vector<std::string> pathElements) {
    const std::string path = fmt::format("{}", fmt::join(pathElements, ", "));
    if (!m_FoldersCache.contains(path)) {
        const int rows = rowCount({});
        beginInsertRows({}, rows, rows);
        TreeItem *item = parent->AppendFolder(pathElements.back());
        endInsertRows();
        m_FoldersCache[path] = item;
    }
    return m_FoldersCache[path];
}
