#pragma once

#include <qstyleoption.h>
#include <QToolButton>

namespace Svch {
    class DisclosureButton : public QToolButton {
        Q_OBJECT

    public:
        explicit DisclosureButton(QWidget *p = nullptr);

        void SetExpanded(const bool on);

        bool IsExpanded() const;

    protected:
        void paintEvent(QPaintEvent *ev) override;

        QSize sizeHint() const override;
    };
}
