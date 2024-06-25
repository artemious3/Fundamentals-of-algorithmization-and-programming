#ifndef STAR6_H
#define STAR6_H

#include "figure.h"

class Star6 : public Base {
public:
    Star6();
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal outerRadius = 100;
    qreal dif = 2;
    int centerX = 0;
    int centerY = 0;
    QRectF boundingRect() const override;
};

#endif // STAR6_H
