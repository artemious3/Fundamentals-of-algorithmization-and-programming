
#include "baseellipse.h"

BaseEllipse::BaseEllipse(QWidget* pointer) : QWidget(pointer) {
  *f = {30, 100};
}

void BaseEllipse::up(QPointF* point, double y) {
  point->ry() -= y;
}

void BaseEllipse::down(QPointF* point, double y) {
  point->ry() += y;
}

void BaseEllipse::paintEvent(QPaintEvent* event) {

  QPainter paint(this);
  paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
  paint.drawEllipse(int(f->rx()), int(f->ry()), 40, 60);

  BaseEllipse::up(f, 0.035);

  if (int(f->ry()) == -60)
    f->ry() = QWidget::height();

  update();
}
