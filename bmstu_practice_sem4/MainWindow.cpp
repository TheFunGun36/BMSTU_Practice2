#include "MainWindow.h"
#include "Scene.h"
#include <qmessagebox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _scene(std::make_shared<Scene>())
    , _renderer(std::make_shared<Renderer>(_scene)) {
    _ui.setupUi(this);

    _ui.displayPort->set_renderer(_renderer);

    connect(_ui.btnRender, &QPushButton::pressed, this, &MainWindow::on_manual_render);
    connect(_ui.actionCubeReset, &QAction::triggered, this, &MainWindow::on_cube_reset);
    connect(_ui.actionCubeUndo, &QAction::triggered, this, &MainWindow::on_cube_undo);
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

    connect(_ui.displayPort, &Viewport::render_succeed, this, &MainWindow::on_render_finish);

    connect(_ui.actionCamL, &QAction::triggered, this, &MainWindow::on_camera_left);
    connect(_ui.actionCamR, &QAction::triggered, this, &MainWindow::on_camera_right);
    connect(_ui.actionCamU, &QAction::triggered, this, &MainWindow::on_camera_up);
    connect(_ui.actionCamD, &QAction::triggered, this, &MainWindow::on_camera_down);

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
    QMessageBox::critical(this, "NOT IMPLEMENTED", "NOT IMPLEMENTED");
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
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate_b() {
    on_rotate('B');
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate_l() {
    on_rotate('L');
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate_r() {
    on_rotate('R');
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate_u() {
    on_rotate('U');
    _ui.displayPort->render_update(false);
    _ui.displayPort->update();
}

void MainWindow::on_rotate_d() {
    on_rotate('D');
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
}

void MainWindow::on_resolution_changed(int value) {
    _ui.displayPort->set_resolution(value);
}

void MainWindow::on_render_simple_changed(int value) {
    _ui.displayPort->set_render_simple(value);
    _ui.statusBar->showMessage("Режим отрисовки переключен в " + value ? "простой" : "полный");
}

void MainWindow::on_render_finish(std::chrono::duration<double, std::milli> delta_time) {
    _ui.statusBar->showMessage("Отрисовка завершена, " + QString::number(delta_time.count()) + " миллисекунд затрачено");
}
