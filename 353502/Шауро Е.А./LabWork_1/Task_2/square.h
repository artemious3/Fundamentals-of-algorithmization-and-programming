#ifndef Square_H
#define Square_H

#include "standart.h"
#include "rectangle.h"

class Square: public Rectangle
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

#endif // Square_H
