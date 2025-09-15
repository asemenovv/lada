#include "InspectorWidget.h"
#include "ui_inspectorwidget.h"

InspectorWidget::InspectorWidget(QWidget *parent)
    : QWidget(parent), ui(std::make_unique<Ui::InspectorWidget>()) {
    ui->setupUi(this);

    auto *root = ui->verticalLayout;

    m_TransformWidget = new Svch::TransformComponentWidget(this);
    m_SecTransform = new Svch::CollapsibleSection("Transform", QIcon(":/icons/xyz"),
        m_TransformWidget, this);
    root->insertWidget(0, m_SecTransform);

    m_CameraWidget = new Svch::CameraComponentWidget(this);
    m_SecCamera = new Svch::CollapsibleSection("Camera", QIcon(":/icons/camera"),
        m_CameraWidget, this);
    root->insertWidget(1, m_SecCamera);

    root->addStretch(1);
}

InspectorWidget::~InspectorWidget() = default;
