#pragma once

#include <QMainWindow>
#include <memory>

#include "scene/SceneTreeModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<SceneTreeModel> m_SceneTreeModel;
    std::vector<Svch::Entity> m_Entities;
};
