#pragma once

#include <memory>

#include "CameraComponentWidget.h"
#include "TransformComponentWidget.h"
#include "components/CollapsibleSection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InspectorWidget; }
QT_END_NAMESPACE

class InspectorWidget : public QWidget {
    Q_OBJECT
public:
    explicit InspectorWidget(QWidget* parent = nullptr);
    ~InspectorWidget() override;
private:
    std::unique_ptr<Ui::InspectorWidget> ui;

    Svch::TransformComponentWidget* m_TransformWidget;
    Svch::CollapsibleSection* m_SecTransform;

    Svch::CameraComponentWidget* m_CameraWidget;
    Svch::CollapsibleSection* m_SecCamera;
};