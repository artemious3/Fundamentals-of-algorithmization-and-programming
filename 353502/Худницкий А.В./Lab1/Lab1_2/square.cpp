#include "square.h"

Square::Square() {}

QRectF Square::boundingRect() const {
    return QRectF(-sidesquare / 2, -sidesquare / 2, sidesquare, sidesquare);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);
    painter->drawRect(-sidesquare / 2, -sidesquare / 2, sidesquare, sidesquare);
}

qreal Square::Perimeter() {

    return 4 * sidesquare;
}

qreal Square::Area() {

    return sidesquare * sidesquare;
}

qreal Square::newArea(qreal number) {

    return sidesquare += number;
}

void Square::newparametrs(double side_1, double side_2, double side_3) {

    sidesquare = side_1;
}
