#include "circle.h"

QRectF Circle::boundingRect() const {
    return QRectF(-radius, -radius, radius * 2, radius * 2);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);
    painter->drawEllipse(0, 0, radius, radius);
}

qreal Circle::Perimeter() {

    return 2 * M_PI * radius;
}

qreal Circle::Area() {

    return M_PI * radius * radius;
}

qreal Circle::newArea(qreal number) {

    return radius += number;
}

void Circle::newparametrs(double side_1, double side_2, double side_3) {

    radius = side_1;
}
