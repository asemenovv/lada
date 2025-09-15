#pragma once

#include <QWidget>
#include <memory>

#include "model/Component.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TransformComponentWidget; }
QT_END_NAMESPACE

namespace Svch {
    class TransformComponentWidget final : public QWidget {
        Q_OBJECT
    public:
        explicit TransformComponentWidget(QWidget* parent = nullptr);
        ~TransformComponentWidget() override;

        void SetTransform(const TransformComponent& transform, bool emitEdited = false);
        TransformComponent Transform() const;

        signals:
        void positionChanged(Vector3f p);
        void rotationChanged(Vector3f rDeg);
        void scaleChanged(Vector3f s);
        void transformEdited(const TransformComponent& t);

    private:
        std::unique_ptr<Ui::TransformComponentWidget> ui;
        bool m_Block = false;

        void connectSignals();
    };
}
