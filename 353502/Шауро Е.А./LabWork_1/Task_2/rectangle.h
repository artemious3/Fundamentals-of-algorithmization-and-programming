#ifndef Rectangle_H
#define Rectangle_H

#include "standart.h"

class Rectangle: public Standart
{
public:
    QRectF boundingRect() const override;

private:
    qreal base = 100;
    qreal coef = 1.5;
protected:
    qreal countPerimeter() override;
    qreal countSquare() override;
    qreal newSquare(qreal con) override;

    void setParameters(qreal param1, qreal param2, qreal param3) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // Rectangle_H
