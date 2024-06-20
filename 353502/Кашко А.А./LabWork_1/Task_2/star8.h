#ifndef STAR8_H
#define STAR8_H

#include "figure.h"

class Star8 : public Base {
public:
    Star8();
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal outerRadius = 100;
    qreal dif = 2;
    int centerX = 0; // центр по оси X
    int centerY = 0; // центр по оси Y
    QRectF boundingRect() const override;
};

#endif // STAR8_H
