#include "DisclosureButton.h"

#include <QPainter>

namespace Svch {
    DisclosureButton::DisclosureButton(QWidget *p): QToolButton(p) {
        setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setCheckable(true);
    }

    void DisclosureButton::SetExpanded(const bool on) {
        setChecked(on);
        update();
    }

    bool DisclosureButton::IsExpanded() const { return isChecked(); }

    void DisclosureButton::paintEvent(QPaintEvent *ev) {
        QToolButton::paintEvent(ev); // нарисует фон, иконку, текст

        // дорисуем стрелку
        QStyleOptionToolButton opt;
        initStyleOption(&opt);

        // где рисовать стрелку (правый край)
        const int m = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &opt, this);
        QRect r = rect().adjusted(m, m, -m, -m);
        const int arrowBox = height() * 0.5;
        QRect arrowRect(r.right() - arrowBox - 5, r.center().y() - arrowBox / 2, arrowBox, arrowBox);

        QStyleOption arrowOpt;
        arrowOpt.initFrom(this);
        arrowOpt.rect = arrowRect;
        arrowOpt.state |= QStyle::State_Enabled;

        QStyle::PrimitiveElement pe = isChecked()
                                          ? QStyle::PE_IndicatorArrowDown
                                          : QStyle::PE_IndicatorArrowRight;

        QPainter p(this);
        style()->drawPrimitive(pe, &arrowOpt, &p, this);
    }

    QSize DisclosureButton::sizeHint() const {
        auto s = QToolButton::sizeHint();
        s.rwidth() += 16; // место под стрелку
        return s;
    }
}
