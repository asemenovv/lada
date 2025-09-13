#include "InspectorWidget.h"
#include "ui_inspectorwidget.h"

InspectorWidget::InspectorWidget(QWidget* parent)
    : QWidget(parent), ui(std::make_unique<Ui::InspectorWidget>()) {
    ui->setupUi(this);
}

InspectorWidget::~InspectorWidget() = default;