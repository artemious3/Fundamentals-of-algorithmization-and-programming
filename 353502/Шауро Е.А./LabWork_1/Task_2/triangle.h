#ifndef Triangle_H
#define Triangle_H

#include "standart.h"

class Triangle: public Standart
{
public:
    QRectF boundingRect() const override;

private:
    qreal sideLength = 100.0;

protected:
    qreal countPerimeter() override;
    qreal countSquare() override;
    qreal newSquare(qreal con) override;

    void setParameters(qreal param1, qreal param2, qreal param3) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // Triangle_H
