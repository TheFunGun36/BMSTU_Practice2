#include "MainWindow.h"
#include "Scene.h"
#include <qmessagebox>
#include <qprogressbar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _scene(std::make_shared<Scene>())
    , _renderer(std::make_shared<Renderer>(_scene)) {
    _ui.setupUi(this);
    _renderer->set_progress_bar(_ui.progressBar);
    _ui.displayPort->set_renderer(_renderer);

    // Change window title
    setWindowTitle("Зеркальный кубик Рубика");

    // Change window icon
    setWindowIcon(QIcon(":/MainWindow/bmstu_logo"));


    //// CONNECT SECTION ////
    
    // Render button
    connect(_ui.btnRender, &QPushButton::pressed, this, &MainWindow::on_manual_render);

    // Render options
    connect(_ui.checkAutoRender, &QCheckBox::stateChanged, this, &MainWindow::on_auto_render_checked);
    connect(_ui.spinScale, &QSpinBox::valueChanged, this, &MainWindow::on_resolution_changed);
    connect(_ui.actionRenderSimple, &QAction::triggered, this, &MainWindow::on_render_simple_changed);

    // Render result
    connect(_ui.displayPort, &Viewport::render_failed, this, &MainWindow::on_render_failed);
    connect(_ui.displayPort, &Viewport::render_succeed, this, &MainWindow::on_render_finish);

    // Cube actions
    connect(_ui.actionCubeReset, &QAction::triggered, this, &MainWindow::on_cube_reset);
    connect(_ui.actionCubeUndo, &QAction::triggered, this, &MainWindow::on_cube_undo);
    connect(_ui.checkRotateRev, &QCheckBox::stateChanged, this, &MainWindow::on_rotate_reverse);
    connect(_ui.btnRotateF, &QPushButton::clicked, this, &MainWindow::on_rotate_f);
    connect(_ui.btnRotateB, &QPushButton::clicked, this, &MainWindow::on_rotate_b);
    connect(_ui.btnRotateL, &QPushButton::clicked, this, &MainWindow::on_rotate_l);
    connect(_ui.btnRotateR, &QPushButton::clicked, this, &MainWindow::on_rotate_r);
    connect(_ui.btnRotateU, &QPushButton::clicked, this, &MainWindow::on_rotate_u);
    connect(_ui.btnRotateD, &QPushButton::clicked, this, &MainWindow::on_rotate_d);

    // Camera actions
    connect(_ui.actionCameraReset, &QAction::triggered, this, &MainWindow::on_camera_reset);
    connect(_ui.actionCamL, &QAction::triggered, this, &MainWindow::on_camera_left);
    connect(_ui.actionCamR, &QAction::triggered, this, &MainWindow::on_camera_right);
    connect(_ui.actionCamU, &QAction::triggered, this, &MainWindow::on_camera_up);
    connect(_ui.actionCamD, &QAction::triggered, this, &MainWindow::on_camera_down);
    connect(_ui.actionZoomIn, &QAction::triggered, this, &MainWindow::on_zoom_in);
    connect(_ui.actionZoomOut, &QAction::triggered, this, &MainWindow::on_zoom_out);

    update_shortcuts();
}


void MainWindow::on_manual_render() {
    _ui.displayPort->render_update(true);
    _ui.displayPort->update();
}

void MainWindow::update_shortcuts() {
    _ui.btnRotateU->setShortcut(QKeySequence('8'));
    _ui.btnRotateL->setShortcut(QKeySequence('U'));
    _ui.btnRotateF->setShortcut(QKeySequence('I'));
    _ui.btnRotateR->setShortcut(QKeySequence('O'));
    _ui.btnRotateD->setShortcut(QKeySequence('K'));
    _ui.btnRotateB->setShortcut(QKeySequence(','));
}

void MainWindow::on_cube_reset(bool checked) {
    _scene->cube_ref().reset();
    _ui.lineHistory->setText(QString::fromStdString(_scene->cube().history()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_cube_undo(bool checked) {
    _scene->cube_ref().undo();
    _ui.lineHistory->setText(QString::fromStdString(_scene->cube().history()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_camera_reset(bool checked) {
    _scene->camera_ref().reset();
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_render_failed() {
    _ui.displayPort->set_auto_render(false);
    _ui.checkAutoRender->setChecked(false);
    QMessageBox::critical(this, "Ошибка", "Не удалось отрисовать сцену");
}

void MainWindow::on_auto_render_checked(int check_state) {
    _ui.displayPort->set_auto_render(check_state);
}

void MainWindow::on_rotate_reverse(int check_state) {
    // not optimal, but looks nice
    _ui.btnRotateF->setText(check_state ? "F'" : "F");
    _ui.btnRotateB->setText(check_state ? "B'" : "B");
    _ui.btnRotateL->setText(check_state ? "L'" : "L");
    _ui.btnRotateR->setText(check_state ? "R'" : "R");
    _ui.btnRotateU->setText(check_state ? "U'" : "U");
    _ui.btnRotateD->setText(check_state ? "D'" : "D");

    update_shortcuts();
}

void MainWindow::on_rotate_f() {
    on_rotate('F');
}

void MainWindow::on_rotate_b() {
    on_rotate('B');
}

void MainWindow::on_rotate_l() {
    on_rotate('L');
}

void MainWindow::on_rotate_r() {
    on_rotate('R');
}

void MainWindow::on_rotate_u() {
    on_rotate('U');
}

void MainWindow::on_rotate_d() {
    on_rotate('D');
}

void MainWindow::on_zoom_in(bool) {
    _scene->camera_ref().zoom_in(camera_zoom);
    _ui.statusBar->showMessage(QString("Камера приближена на ")
        + QString::number(camera_zoom));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_zoom_out(bool) {
    _scene->camera_ref().zoom_out(camera_zoom);
    _ui.statusBar->showMessage(QString("Камера отдалена на ")
        + QString::number(camera_zoom));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_camera_left(bool) {
    _scene->camera_ref().rotate_horizontal(-camera_rotation);
    _ui.statusBar->showMessage(QString("Камера повёрнута по горизонтали на ")
        + QString::fromStdString((-camera_rotation).to_string()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}
void MainWindow::on_camera_right(bool) {
    _scene->camera_ref().rotate_horizontal(camera_rotation);
    _ui.statusBar->showMessage(QString("Камера повёрнута по горизонтали на ")
        + QString::fromStdString(camera_rotation.to_string()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}
void MainWindow::on_camera_up(bool) {
    _scene->camera_ref().rotate_vertical(camera_rotation);
    _ui.statusBar->showMessage(QString("Камера повёрнута по вертикали на ")
        + QString::fromStdString(camera_rotation.to_string()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}
void MainWindow::on_camera_down(bool) {
    _scene->camera_ref().rotate_vertical(-camera_rotation);
    _ui.statusBar->showMessage(QString("Камера повёрнута по вертикали на ")
        + QString::fromStdString((-camera_rotation).to_string()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate(char direction) {
    _scene->cube_ref().rotate(direction, _ui.checkRotateRev->isChecked());
    _ui.lineHistory->setText(QString::fromStdString(_scene->cube().history()));
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_resolution_changed(int value) {
    _ui.displayPort->set_resolution(value);
}

void MainWindow::on_render_simple_changed(int value) {
    _ui.displayPort->set_render_simple(value);
    _ui.statusBar->showMessage(QString("Режим отрисовки переключен в ") + (value ? QString("простой") : QString("полный")));
}

void MainWindow::on_render_finish(std::chrono::duration<double, std::milli> delta_time, int pixels) {
    _ui.statusBar->showMessage(
        "Отрисовка завершена, "
        + QString::number(delta_time.count())
        + " миллисекунд затрачено, "
        + QString::number(pixels)
        + "пикселей отрисовано.");
}
