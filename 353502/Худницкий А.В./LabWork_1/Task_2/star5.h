#ifndef STAR5_H
#define STAR5_H

#include "figure.h"

class Star5 : public Base {
public:
    Star5();
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

#endif // STAR5_H
