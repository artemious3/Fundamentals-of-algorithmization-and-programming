#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Base {
public:
    Rhombus();
    qreal Perimeter();
    qreal Area();
    qreal newArea(qreal number);
    void newparametrs(double side_1, double side_2, double side_3) override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal diagonal1 = 60;
    qreal difr = 20;
    qreal siderhombus = sqrt(diagonal1 * diagonal1 - (diagonal1 - 20) * (diagonal1 - 20));
    QRectF boundingRect() const override;
};

#endif // RHOMBUS_H
