#ifndef HEXAGON_H
#define HEXAGON_H

#include "triangle.h"

class Hexagon : public Triangle
{

public:
    QRectF boundingRect() const override;

private:
    qreal radius = 100.0;

protected:
    qreal countPerimeter() override;
    qreal countSquare() override;
    qreal newSquare(qreal con) override;

    void setParameters(qreal param1, qreal param2, qreal param3) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};
#endif // HEXAGON_H
