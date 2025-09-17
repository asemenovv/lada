#include "MeshComponentWidget.h"

#include "ui_meshcomponentwidget.h"

namespace Svch {
    MeshComponentWidget::MeshComponentWidget(QWidget *parent)
        : QWidget(parent), ui(std::make_unique<Ui::MeshComponentWidget>()) {
        ui->setupUi(this);
    }

    MeshComponentWidget::~MeshComponentWidget() = default;
}
