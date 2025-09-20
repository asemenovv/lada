#pragma once

#include <QtCore/QPointF>
#include <QtCore/QSize>
#include <QtNodes/AbstractGraphModel>

#include <unordered_set>

#include "model/shader/NodeElement.h"

class ShaderGraphModel : public QtNodes::AbstractGraphModel {
    Q_OBJECT
public:
    struct NodeGeometryData
    {
        QSize size;
        QPointF pos;
    };

public:
    ShaderGraphModel();

    ~ShaderGraphModel() override;

    std::unordered_set<QtNodes::NodeId> allNodeIds() const override;

    std::unordered_set<QtNodes::ConnectionId> allConnectionIds(QtNodes::NodeId nodeId) const override;

    std::unordered_set<QtNodes::ConnectionId> connections(QtNodes::NodeId nodeId,
                                                          QtNodes::PortType portType,
                                                          QtNodes::PortIndex portIndex) const override;

    bool connectionExists(QtNodes::ConnectionId connectionId) const override;

    QtNodes::NodeId addNode(QString nodeType = QString()) override;

    QtNodes::NodeId newNodeId() override;

    bool connectionPossible(QtNodes::ConnectionId connectionId) const override;

    void addConnection(QtNodes::ConnectionId connectionId) override;

    bool nodeExists(QtNodes::NodeId nodeId) const override;

    QVariant nodeData(QtNodes::NodeId nodeId, QtNodes::NodeRole role) const override;

    bool setNodeData(QtNodes::NodeId nodeId, QtNodes::NodeRole role, QVariant value) override;

    void SetNodeModel(QtNodes::NodeId nodeId, const std::shared_ptr<Svch::NodeElement> &model);

    QVariant portData(QtNodes::NodeId nodeId,
                      QtNodes::PortType portType,
                      QtNodes::PortIndex portIndex,
                      QtNodes::PortRole role) const override;

    bool setPortData(QtNodes::NodeId nodeId,
                     QtNodes::PortType portType,
                     QtNodes::PortIndex portIndex,
                     QVariant const &value,
                     QtNodes::PortRole role) override;

    bool deleteConnection(QtNodes::ConnectionId const connectionId) override;

    bool deleteNode(QtNodes::NodeId const nodeId) override;

private:
    QtNodes::NodeId m_NextNodeId;
    std::unordered_set<QtNodes::NodeId> m_NodeIds;
    mutable std::unordered_map<QtNodes::NodeId, std::shared_ptr<Svch::NodeElement>> m_NodeModels;
    std::unordered_set<QtNodes::ConnectionId> m_Connectivity;
    mutable std::unordered_map<QtNodes::NodeId, NodeGeometryData> m_NodeGeometryData;
};
