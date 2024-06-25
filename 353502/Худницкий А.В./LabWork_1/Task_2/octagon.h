#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"

class Trapezoid : public Base {
public:
    Trapezoid();
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const override;

    qreal side1 = 50; // Длина стороны восьмиугольника
};

#endif // OCTAGON_H
