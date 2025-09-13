#pragma once

#include <QWidget>
#include <memory>

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
};