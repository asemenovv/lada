#include "ShaderGraphModel.h"

#include <QtNodes/ConnectionIdUtils>

#include "QtNodes/internal/StyleCollection.hpp"

ShaderGraphModel::ShaderGraphModel() {
}

ShaderGraphModel::~ShaderGraphModel() {
}

std::unordered_set<QtNodes::NodeId> ShaderGraphModel::allNodeIds() const {
    return m_NodeIds;
}

std::unordered_set<QtNodes::ConnectionId> ShaderGraphModel::allConnectionIds(QtNodes::NodeId const nodeId) const {
    std::unordered_set<QtNodes::ConnectionId> result;

    std::ranges::copy_if(m_Connectivity,
                         std::inserter(result, std::end(result)),
                         [&nodeId](QtNodes::ConnectionId const &cid) {
                             return cid.inNodeId == nodeId || cid.outNodeId == nodeId;
                         });

    return result;
}

std::unordered_set<QtNodes::ConnectionId> ShaderGraphModel::connections(QtNodes::NodeId nodeId,
                                                                        QtNodes::PortType portType,
                                                                        QtNodes::PortIndex portIndex) const {
    std::unordered_set<QtNodes::ConnectionId> result;

    std::ranges::copy_if(m_Connectivity,
                         std::inserter(result, std::end(result)),
                         [&portType, &portIndex, &nodeId](QtNodes::ConnectionId const &cid) {
                             return (getNodeId(portType, cid) == nodeId
                                     && getPortIndex(portType, cid) == portIndex);
                         });
    return result;
}

bool ShaderGraphModel::connectionExists(QtNodes::ConnectionId const connectionId) const {
    return m_Connectivity.contains(connectionId);
}

QtNodes::NodeId ShaderGraphModel::addNode(QString const nodeType) {
    const QtNodes::NodeId newId = newNodeId();
    m_NodeIds.insert(newId);
    Q_EMIT nodeCreated(newId);
    return newId;
}

QtNodes::NodeId ShaderGraphModel::newNodeId() {
    return m_NextNodeId++;
}

bool ShaderGraphModel::connectionPossible(QtNodes::ConnectionId const connectionId) const {
    if (!connections(connectionId.inNodeId, QtNodes::PortType::In, connectionId.inPortIndex).empty()) {
        return false;
    }
    return !m_Connectivity.contains(connectionId);
}

void ShaderGraphModel::addConnection(QtNodes::ConnectionId const connectionId) {
    m_Connectivity.insert(connectionId);
    Q_EMIT connectionCreated(connectionId);
}

bool ShaderGraphModel::nodeExists(QtNodes::NodeId const nodeId) const {
    return (m_NodeIds.contains(nodeId));
}

QVariant ShaderGraphModel::nodeData(const QtNodes::NodeId nodeId, const QtNodes::NodeRole role) const {
    switch (role) {
        case QtNodes::NodeRole::Type:
            return  QString("Default Node Type");
        case QtNodes::NodeRole::Position:
            return m_NodeGeometryData[nodeId].pos;
        case QtNodes::NodeRole::Size:
            return m_NodeGeometryData[nodeId].size;
        case QtNodes::NodeRole::CaptionVisible:
            return true;
        case QtNodes::NodeRole::Caption:
            if (m_NodeModels.contains(nodeId)) {
                return QString(m_NodeModels[nodeId]->GetCaption().c_str());
            }
            return QString("Node");
        case QtNodes::NodeRole::Style: {
            auto style = QtNodes::StyleCollection::nodeStyle();
            if (m_NodeModels.contains(nodeId)) {
                switch (m_NodeModels[nodeId]->GetNodeType()) {
                    case Svch::NodeType::INPUT:
                        style.FontColor = QColor(0xfacc15);
                        break;
                    case Svch::NodeType::OUTPUT:
                        style.FontColor = QColor(0x4ade80);
                        break;
                    case Svch::NodeType::OPERATION:
                        style.FontColor = QColor(0x60a5fa);
                        break;
                    case Svch::NodeType::NOP:
                        break;
                }
            }
            return style.toJson().toVariantMap();
        }
        case QtNodes::NodeRole::InPortCount: {
            if (m_NodeModels.contains(nodeId)) {
                return m_NodeModels[nodeId]->InputPorts();
            }
            return 0u;
        }
        case QtNodes::NodeRole::OutPortCount:
            if (m_NodeModels.contains(nodeId)) {
                return m_NodeModels[nodeId]->OutputPorts();
            }
            return 0u;
        case QtNodes::NodeRole::Widget:
        case QtNodes::NodeRole::InternalData:
        default:
            return {};
    }
}

bool ShaderGraphModel::setNodeData(QtNodes::NodeId nodeId, QtNodes::NodeRole role, QVariant value) {
    switch (role) {
        case QtNodes::NodeRole::Position:
            m_NodeGeometryData[nodeId].pos = value.value<QPointF>();
            Q_EMIT nodePositionUpdated(nodeId);
            return true;
        case QtNodes::NodeRole::Size:
            m_NodeGeometryData[nodeId].size = value.value<QSize>();
            return true;
        case QtNodes::NodeRole::CaptionVisible:
        case QtNodes::NodeRole::Caption:
        case QtNodes::NodeRole::Style:
        case QtNodes::NodeRole::InternalData:
        case QtNodes::NodeRole::InPortCount:
        case QtNodes::NodeRole::OutPortCount:
        case QtNodes::NodeRole::Type:
        case QtNodes::NodeRole::Widget:
        default:
            return false;

    }
}

void ShaderGraphModel::SetNodeModel(const QtNodes::NodeId nodeId, Svch::NodeElement* model) {
    m_NodeModels[nodeId] = model;
    Q_EMIT nodeUpdated(nodeId);
}

QVariant ShaderGraphModel::portData(QtNodes::NodeId nodeId, QtNodes::PortType portType, QtNodes::PortIndex portIndex,
                                    QtNodes::PortRole role) const {
    switch (role) {
        case QtNodes::PortRole::Data:
            return QVariant();

        case QtNodes::PortRole::DataType:
            return QVariant();

        case QtNodes::PortRole::ConnectionPolicyRole:
            switch (portType) {
                case QtNodes::PortType::In:
                    return QVariant::fromValue(QtNodes::ConnectionPolicy::One);
                case QtNodes::PortType::Out:
                    return QVariant::fromValue(QtNodes::ConnectionPolicy::Many);
                case QtNodes::PortType::None:
                    return QVariant::fromValue(QtNodes::ConnectionPolicy::One);
            }

        case QtNodes::PortRole::CaptionVisible:
            return true;

        case QtNodes::PortRole::Caption:
            if (portType == QtNodes::PortType::In)
                return QString::fromUtf8("Port In");
            else
                return QString::fromUtf8("Port Out");
    }
    return QVariant();
}

bool ShaderGraphModel::setPortData(const QtNodes::NodeId nodeId, const QtNodes::PortType portType,
    const QtNodes::PortIndex portIndex, QVariant const &value, const QtNodes::PortRole role) {
    Q_UNUSED(nodeId);
    Q_UNUSED(portType);
    Q_UNUSED(portIndex);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return false;
}

bool ShaderGraphModel::deleteConnection(QtNodes::ConnectionId const connectionId) {
    bool disconnected = false;

    auto it = m_Connectivity.find(connectionId);
    if (it != m_Connectivity.end()) {
        disconnected = true;
        m_Connectivity.erase(it);
    }

    if (disconnected)
        Q_EMIT connectionDeleted(connectionId);

    return disconnected;
}

bool ShaderGraphModel::deleteNode(QtNodes::NodeId const nodeId) {
    const auto connectionIds = allConnectionIds(nodeId);
    for (auto &cId: connectionIds) {
        deleteConnection(cId);
    }
    m_NodeIds.erase(nodeId);
    m_NodeGeometryData.erase(nodeId);
    m_NodeModels.erase(nodeId);

    Q_EMIT nodeDeleted(nodeId);

    return true;
}
