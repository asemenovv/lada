#pragma once

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QFrame>

namespace Svch {
    class CollapsibleSection final : public QWidget {
        Q_OBJECT
    public:
        explicit CollapsibleSection(const QString& title, QIcon icon,
            QWidget* contentWidget = nullptr, QWidget* parent = nullptr);

        void SetContent(QWidget* widget);
        [[nodiscard]] QWidget* content() const { return m_Content; }

        void setExpanded(bool expanded) const;
        [[nodiscard]] bool isExpanded() const { return m_Button->isChecked(); }
    private:
        QToolButton* m_Button;
        QFrame* m_ContentFrame;
        QWidget* m_Content{nullptr};

        std::unique_ptr<QVBoxLayout> layout;
        std::unique_ptr<QHBoxLayout> contentLayout;
    };
}
