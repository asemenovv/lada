#include "CameraComponentWidget.h"

#include "ui_cameracomponentwidget.h"

namespace Svch {
    CameraComponentWidget::CameraComponentWidget(QWidget *parent)
        : QWidget(parent), ui(std::make_unique<Ui::CameraComponentWidget>()) {
        ui->setupUi(this);
    }

    CameraComponentWidget::~CameraComponentWidget() = default;
}
