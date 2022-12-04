#pragma once
#include <qwidget.h>
#include "Renderer.h"
#include "Property.h"

class Viewport : public QWidget {
    Q_OBJECT

public:
    PROPERTY_RW(std::shared_ptr<Renderer>, renderer);
    PROPERTY_RW(bool, auto_render);
    PROPERTY_RW(bool, render_simple);
    PROPERTY_RW(int, resolution);

public:
    Viewport(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* e) override;

    void render_update(bool force = false);

private:
    bool _should_render;
    QPixmap _pixmap;

signals:
    void render_failed();
    void render_succeed(std::chrono::duration<double, std::milli> delta_time, int pixels);
};

