#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Base {
public:
    Square();
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal sidesquare = 40;
    QRectF boundingRect() const override;
};

#endif // SQUARE_H
