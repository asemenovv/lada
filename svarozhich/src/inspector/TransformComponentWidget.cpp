#include "TransformComponentWidget.h"

#include "ui_transformcomponentwidget.h"

#include <QDoubleSpinBox>

namespace Svch {
    TransformComponentWidget::TransformComponentWidget(QWidget *parent)
        :QWidget(parent), ui(std::make_unique<Ui::TransformComponentWidget>()) {
        ui->setupUi(this);
        connectSignals();

        SetTransform(TransformComponent{});
    }

    TransformComponentWidget::~TransformComponentWidget() {}

    void TransformComponentWidget::SetTransform(const TransformComponent &transform, bool emitEdited) {
        m_Block = true;
        ui->posX->setValue(transform.GetPosition().x);
        ui->posY->setValue(transform.GetPosition().y);
        ui->posZ->setValue(transform.GetPosition().z);

        ui->rotX->setValue(transform.GetRotation().x);
        ui->rotY->setValue(transform.GetRotation().y);
        ui->rotZ->setValue(transform.GetRotation().z);

        ui->sclX->setValue(std::max(0.0001, static_cast<double>(transform.GetScale().x)));
        ui->sclY->setValue(std::max(0.0001, static_cast<double>(transform.GetScale().y)));
        ui->sclZ->setValue(std::max(0.0001, static_cast<double>(transform.GetScale().z)));
        m_Block = false;

        if (emitEdited) emit transformEdited(Transform());
    }

    TransformComponent TransformComponentWidget::Transform() const {
        TransformComponent t;
        t.SetPosition({float(ui->posX->value()), float(ui->posY->value()), float(ui->posZ->value())});
        t.SetRotation({float(ui->rotX->value()), float(ui->rotY->value()), float(ui->rotZ->value())});
        t.SetScale({
            float(std::max(0.0001, ui->sclX->value())),
            float(std::max(0.0001, ui->sclY->value())),
            float(std::max(0.0001, ui->sclZ->value()))
        });
        return t;
    }

    void TransformComponentWidget::connectSignals() {
        auto emitPos = [this] {
            if (m_Block) return;
            const auto t = Transform();
            emit positionChanged(t.GetPosition());
            emit transformEdited(t);
        };
        auto emitRot = [this] {
            if (m_Block) return;
            const auto t = Transform();
            emit rotationChanged(t.GetRotation());
            emit transformEdited(t);
        };
        auto emitScl = [this] {
            if (m_Block) return;
            const auto t = Transform();
            emit scaleChanged(t.GetScale());
            emit transformEdited(t);
        };

        // Лучше на editingFinished для поз/рот, а scale можно на valueChanged
        connect(ui->posX, &QDoubleSpinBox::editingFinished, this, emitPos);
        connect(ui->posY, &QDoubleSpinBox::editingFinished, this, emitPos);
        connect(ui->posZ, &QDoubleSpinBox::editingFinished, this, emitPos);

        connect(ui->rotX, &QDoubleSpinBox::editingFinished, this, emitRot);
        connect(ui->rotY, &QDoubleSpinBox::editingFinished, this, emitRot);
        connect(ui->rotZ, &QDoubleSpinBox::editingFinished, this, emitRot);

        connect(ui->sclX, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [emitScl](double) { emitScl(); });
        connect(ui->sclY, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [emitScl](double) { emitScl(); });
        connect(ui->sclZ, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [emitScl](double) { emitScl(); });
    }
}
