#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rect : public Base {
public:
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal side1 = 90;
    qreal dif = 50;
    QRectF boundingRect() const override;
};

#endif // RECTANGLE_H
