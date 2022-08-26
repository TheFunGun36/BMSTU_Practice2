#include "Viewport.h"
#include <qpainter.h>
#include <qimage.h>

Viewport::Viewport(QWidget* parent)
    : QWidget(parent) {

}

void Viewport::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    QPainter qp(this);
    QPixmap pixmap(width(), height());
    QImage image = pixmap.toImage();
    _renderer->render(image);
    qp.drawPixmap(0, 0, QPixmap::fromImage(image));
}
