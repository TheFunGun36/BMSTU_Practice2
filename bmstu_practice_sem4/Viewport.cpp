#include "Viewport.h"
#include <qpainter.h>
#include <qimage.h>

Viewport::Viewport(QWidget* parent)
    : QWidget(parent)
    , _pixmap(width(), height())
    , _should_render(false)
    , _auto_render(false) {
}

void Viewport::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    QPainter qp(this);

    if (_should_render) {
        QImage image = QPixmap(width(), height()).toImage();
        _renderer->render(image);
        _pixmap = QPixmap::fromImage(image);
    }
    qp.drawPixmap(0, 0, _pixmap);
}

void Viewport::render_update(bool manual) {
    _should_render = _auto_render || manual;
}
