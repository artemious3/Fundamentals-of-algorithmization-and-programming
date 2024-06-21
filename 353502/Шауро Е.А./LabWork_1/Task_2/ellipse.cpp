#include "ellipse.h"


//отрисовка квадрата, в который влазит треугольник
QRectF Ellipse::boundingRect() const{
    return QRectF(-20, -10, myY, 70);
}


void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen;
    pen.setColor(Qt::black);


    painter->setPen(pen);
    painter->drawEllipse(-20, -10, myY, 70);
    //Q_UNUSED(option);
    //Q_UNUSED(widget);
};
























