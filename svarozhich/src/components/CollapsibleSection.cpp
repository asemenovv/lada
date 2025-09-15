#include "CollapsibleSection.h"

#include "DisclosureButton.h"

namespace Svch {
    CollapsibleSection::CollapsibleSection(const QString &title, QIcon icon, QWidget *contentWidget, QWidget *parent)
        : QWidget(parent), m_Button(new DisclosureButton(this)), m_ContentFrame(new QFrame(this)) {
        m_Button->setText(title);
        m_Button->setIcon(icon);
        m_Button->setIconSize(QSize(16, 16));
        m_Button->setCheckable(true);
        m_Button->setChecked(true);
        m_Button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        layout = std::make_unique<QVBoxLayout>(this);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(m_Button);
        layout->addWidget(m_ContentFrame);

        contentLayout = std::make_unique<QHBoxLayout>(m_ContentFrame);
        contentLayout->setSpacing(0);
        contentLayout->setContentsMargins(0, 4, 0, 4);

        if (contentWidget) {
            SetContent(contentWidget);
        }

        connect(m_Button, &QToolButton::toggled, this, [this](const bool checked) {
            m_ContentFrame->setVisible(checked);
            static_cast<DisclosureButton*>(m_Button)->SetExpanded(checked);
        });
    }

    void CollapsibleSection::SetContent(QWidget *widget) {
        if (m_Content) {
            m_Content->setParent(nullptr);
        }
        m_Content = widget;
        if (widget) {
            m_ContentFrame->layout()->addWidget(widget);
        }
    }

    void CollapsibleSection::setExpanded(const bool expanded) const {
        m_Button->setChecked(expanded);
        m_ContentFrame->setVisible(expanded);
        m_Button->setArrowType(expanded ? Qt::DownArrow : Qt::RightArrow);
    }
}
