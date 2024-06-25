#include "rect.h"
#include "figure.h"

QRectF Rect::boundingRect() const {
    return QRectF(-side1 / 2, -(side1 - dif) / 2, side1 * 2, (side1 - dif) * 2);
}

void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);
    painter->drawRect(0, 0, side1, side1 - dif);
}

qreal Rect::Perimeter() {

    return 2 * (side1 + side1 - dif);
}

qreal Rect::Area() {

    return side1 * (side1 - dif);
}

qreal Rect::newArea(qreal number) {

    return side1 += number;
}

void Rect::newparametrs(double side_1, double side_2, double side_3) {

    if (side_2 == 0) {
        side_2 = side1 - dif;
    }
    if (side_1 == 0) {
        side_1 = side1;
    }
    if (side_1 >= side_2) {
        side1 = side_1;
        dif = abs(side_2 - side_1);
    }
    else {
        side1 = side_1;
        dif = -side_2 + side_1;
    }
}


