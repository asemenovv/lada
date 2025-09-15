#pragma once

#include <QWidget>
#include <memory>

#include "model/Component.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CameraComponentWidget; }
QT_END_NAMESPACE

namespace Svch {
    class CameraComponentWidget final : public QWidget {
        Q_OBJECT
    public:
        explicit CameraComponentWidget(QWidget* parent = nullptr);
        ~CameraComponentWidget() override;
    private:
        std::unique_ptr<Ui::CameraComponentWidget> ui;
    };
}
