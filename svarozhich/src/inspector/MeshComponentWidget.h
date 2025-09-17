#pragma once

#include <QWidget>
#include <QColor>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MeshComponentWidget; }
QT_END_NAMESPACE

namespace Svch {
    class MeshComponentWidget final : public QWidget {
        Q_OBJECT
    public:
        explicit MeshComponentWidget(QWidget* parent = nullptr);
        ~MeshComponentWidget() override;
    private:
        std::unique_ptr<Ui::MeshComponentWidget> ui;
    };
}
