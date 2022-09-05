#include "MainWindow.h"
#include "Scene.h"
#include <qmessagebox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _scene(std::make_shared<Scene>())
    , _renderer(std::make_shared<Renderer>(_scene)) {
    _ui.setupUi(this);

    // Assign scene renderer to viewport
    _ui.displayPort->set_renderer(_renderer);

    // Load scene
    //_scene->load("Scene.json");

    // connect everything lol

    connect(_ui.btnRender, &QPushButton::pressed, this, &MainWindow::on_manual_render);
    connect(_ui.actionCubeReset, &QAction::triggered, this, &MainWindow::on_cube_reset);
    connect(_ui.actionCubeUndo, &QAction::triggered, this, &MainWindow::on_cube_undo);
    connect(_ui.actionSceneLoad, &QAction::triggered, this, &MainWindow::on_scene_load);
    connect(_ui.actionCameraReset, &QAction::triggered, this, &MainWindow::on_camera_reset);
    connect(_ui.checkAutoRender, &QCheckBox::stateChanged, this, &MainWindow::on_auto_render_checked);

    connect(_ui.displayPort, &Viewport::render_failed, this, &MainWindow::on_render_failed);

    connect(_ui.btnRotateF, &QPushButton::clicked, this, &MainWindow::on_rotate_f);
    connect(_ui.btnRotateB, &QPushButton::clicked, this, &MainWindow::on_rotate_b);
    connect(_ui.btnRotateL, &QPushButton::clicked, this, &MainWindow::on_rotate_l);
    connect(_ui.btnRotateR, &QPushButton::clicked, this, &MainWindow::on_rotate_r);
    connect(_ui.btnRotateU, &QPushButton::clicked, this, &MainWindow::on_rotate_u);
    connect(_ui.btnRotateD, &QPushButton::clicked, this, &MainWindow::on_rotate_d);

    connect(_ui.checkRotateRev, &QCheckBox::stateChanged, this, &MainWindow::on_rotate_reverse);
    connect(_ui.spinScale, &QSpinBox::valueChanged, this, &MainWindow::on_resolution_changed);
    connect(_ui.actionRenderSimple, &QAction::triggered, this, &MainWindow::on_render_simple_changed);
}


void MainWindow::on_manual_render() {
    _ui.displayPort->render_update(true);
    _ui.displayPort->update();
}

void MainWindow::on_cube_reset(bool checked) {
    QMessageBox::critical(this, "NOT IMPLEMENTED", "NOT IMPLEMENTED");
}

void MainWindow::on_cube_undo(bool checked) {
    QMessageBox::critical(this, "NOT IMPLEMENTED", "NOT IMPLEMENTED");
}

void MainWindow::on_scene_load(bool checked) {
    QMessageBox::critical(this, "NOT IMPLEMENTED", "NOT IMPLEMENTED");
}

void MainWindow::on_camera_reset(bool checked) {
    QMessageBox::critical(this, "NOT IMPLEMENTED", "NOT IMPLEMENTED");
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

void MainWindow::on_rotate(char direction) {
    _scene->cube()->rotate(direction, _ui.checkRotateRev->isChecked());
    _ui.lineHistory->setText(QString::fromStdString(_scene->cube()->history()));
}

void MainWindow::on_resolution_changed(int value) {
    _ui.displayPort->set_resolution(value);
}

void MainWindow::on_render_simple_changed(int value) {
    _ui.displayPort->set_render_simple(value);
}
