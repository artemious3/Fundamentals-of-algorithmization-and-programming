#ifndef RECT_H
#define RECT_H

#include "figure.h"

class Rect : public Base {
public:
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal side1 = 100;
    qreal dif = 60;
    QRectF boundingRect() const override;
};

#endif // RECT_H
