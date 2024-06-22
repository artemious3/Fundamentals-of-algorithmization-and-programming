#include "triangle.h"

Triangle::Triangle() {}

QRectF Triangle::boundingRect() const {
    return QRectF((-sideLength / 2) - 10, (-sideLength / 2) - 10, sideLength + 10, sideLength + 10);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);

    QPolygonF triangle;

    QPointF center(0, 0);

    QPointF point1(center.x(), center.y() - sqrt(3.0) / 3 * sideLength);
    QPointF point2(center.x() + sideLength / 2, center.y() + sqrt(3.0) / 6 * sideLength);
    QPointF point3(center.x() - sideLength / 2, center.y() + sqrt(3.0) / 6 * sideLength);

    triangle << point1 << point2 << point3;
    painter->drawPolygon(triangle);
}

qreal Triangle::Perimeter() {

    return sideLength * 3;
}

qreal Triangle::Area() {

    return sideLength * sideLength * sqrt(3) / 4;
}

qreal Triangle::newArea(qreal number) {

    return sideLength += number;
}

void Triangle::newparametrs(double side_1, double side_2, double side_3) {

    sideLength = side_1;
}
