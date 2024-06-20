#include "rectangle.h"

rectangle::rectangle(QWidget *pobj) {
    *f = {30, 100};
}

void rectangle::paintEvent(QPaintEvent *pe) {

    QWidget::paintEvent(pe);
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(int(f->rx()), int(f->ry()), 105, 60);

    if (int(f->rx()) == -60) f->rx() = QWidget::height();

    movement::Left(f, 0.015);

    update();
}
