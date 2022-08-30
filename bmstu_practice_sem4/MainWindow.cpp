#include "MainWindow.h"
#include "Scene.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _scene(std::make_shared<Scene>())
    , _renderer(std::make_shared<Renderer>(_scene)) {
    _ui.setupUi(this);

    // Assign scene renderer to viewport
    _ui.displayPort->set_renderer(_renderer);

    // Load scene
    //_scene->load("Scene.json");
}
