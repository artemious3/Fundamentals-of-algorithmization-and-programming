#include "rhombus.h"

Rhombus::Rhombus() {}

QRectF Rhombus::boundingRect() const {
    return QRectF(-diagonal1 / 2, -(diagonal1 - difr) / 2, diagonal1, diagonal1 - difr);
}

void Rhombus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);

    QPolygonF rhombusPolygon;

    QPointF center(0, 0);

    QPointF point1(center.x() + diagonal1 / 2, center.y());
    QPointF point2(center.x(), center.y() - (diagonal1 - difr) / 2);
    QPointF point3(center.x() - diagonal1 / 2, center.y());
    QPointF point4(center.x(), center.y() + (diagonal1 - difr) / 2);

    rhombusPolygon << point1 << point2 << point3 << point4;
    painter->drawPolygon(rhombusPolygon);
}

qreal Rhombus::Perimeter() {

    return 4 * siderhombus;
}

qreal Rhombus::Area() {

    return diagonal1 * (diagonal1 - difr) / 2;
}

qreal Rhombus::newArea(qreal number) {

    return diagonal1 += number;
}

void Rhombus::newparametrs(double side_1, double side_2, double side_3) {

    if (side_2 == 0) {
        side_2 = diagonal1 - difr;
    }
    if (side_1 == 0) {
        side_1 = diagonal1;
    }
    if (side_1 >= side_2) {
        diagonal1 = side_1;
        difr = abs(side_2 - side_1);
    }
    else {
        diagonal1 = side_1;
        difr = -side_2 + side_1;
    }
}
