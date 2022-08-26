#include "MainWindow.h"
#include "Scene.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _scene(std::make_shared<Scene>()) {
    _ui.setupUi(this);
    _ui.displayPort->set_renderer(_scene->renderer());
}
