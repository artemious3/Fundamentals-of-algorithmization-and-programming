#ifndef Star6_H
#define Star6_H

#include "triangle.h"

class Star6 : public Triangle
{

public:
    QRectF boundingRect() const override;

private:
    qreal radius = 50;
    qreal coef = 2;

    QPointF center = QPoint(0,0);

protected:
    qreal countPerimeter() override;
    qreal countSquare() override;
    qreal newSquare(qreal con) override;

    void setParameters(qreal param1, qreal param2, qreal param3) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


};
#endif // Star6_H
