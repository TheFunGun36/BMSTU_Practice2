#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
class Scene;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass _ui;
    std::shared_ptr<Scene> _scene;
    std::shared_ptr<Renderer> _renderer;
};
