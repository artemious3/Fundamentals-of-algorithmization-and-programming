#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Base {
public:
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal radius = 50;
    QRectF boundingRect() const override;
};

#endif // CIRCLE_H
