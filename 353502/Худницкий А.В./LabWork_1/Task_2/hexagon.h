#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"

class Hexagon : public Base {
public:
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal side = 100;
    QRectF boundingRect() const override;
};

#endif // HEXAGON_H
