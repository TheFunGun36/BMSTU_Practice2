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
    Angle camera_rotation = Angle::from_degrees(15);
    real camera_zoom = 25.0;

    void update_shortcuts();

private slots:
    void on_manual_render();
    void on_cube_reset(bool checked);
    void on_cube_undo(bool checked);
    void on_camera_reset(bool checked);
    void on_render_failed();
    void on_auto_render_checked(int check_state);
    void on_rotate_reverse(int check_state);
    void on_rotate_f();
    void on_rotate_b();
    void on_rotate_l();
    void on_rotate_r();
    void on_rotate_u();
    void on_rotate_d();
    void on_zoom_in(bool);
    void on_zoom_out(bool);
    void on_rotate(char direction);
    void on_resolution_changed(int value);
    void on_render_simple_changed(int value);
    void on_render_finish(std::chrono::duration<double, std::milli> delta_time, int pixels);

    void on_camera_left(bool);
    void on_camera_right(bool);
    void on_camera_up(bool);
    void on_camera_down(bool);
};
