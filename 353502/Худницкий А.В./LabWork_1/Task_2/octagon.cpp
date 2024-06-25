#include "octagon.h"

Trapezoid::Trapezoid() {}

QRectF Trapezoid::boundingRect() const {
    return QRectF(-side1 / 2 / sin(M_PI / 8), -side1 / 2 / sin(M_PI / 8), side1 / tan(M_PI / 8), side1 / tan(M_PI / 8));
}

void Trapezoid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);

    QPolygonF octagonPolygon;

    QPointF center(0, 0);

    for (int i = 0; i < 8; ++i) {
        qreal angle = i * M_PI / 4;
        QPointF point(center.x() + side1 * cos(angle), center.y() + side1 * sin(angle));
        octagonPolygon << point;
    }

    painter->drawPolygon(octagonPolygon);
}

qreal Trapezoid::Perimeter() {

    return 8 * side1;
}

qreal Trapezoid::Area() {

    return 2 * side1 * side1 * (1 + sqrt(2));
}

qreal Trapezoid::newArea(qreal number) {

    return side1 += number;
}

void Trapezoid::newparametrs(double side_1, double side_2, double side_3) {

    side1 = side_1;
}

