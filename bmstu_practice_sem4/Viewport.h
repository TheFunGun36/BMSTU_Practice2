#pragma once
#include <qwidget.h>
#include "Renderer.h"
#include "Property.h"

class Viewport : public QWidget {
    Q_OBJECT

public:
    PROPERTY_RW(std::shared_ptr<Renderer>, renderer);

public:
    Viewport(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* e) override;
};

