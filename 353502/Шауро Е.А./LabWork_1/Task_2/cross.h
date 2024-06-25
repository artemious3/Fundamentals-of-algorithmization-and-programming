#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "standart.h"

class Cross: public Standart
{

public:
    QRectF boundingRect() const override;

private:
    qreal coef = 1;
    qreal lenHor = 100;
    qreal width = 20;

protected:
    qreal countPerimeter() override;
    qreal countSquare() override;
    qreal newSquare(qreal con) override;

    void setParameters(qreal param1, qreal param2, qreal param3) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


};

#endif // TRAPEZOID_H

