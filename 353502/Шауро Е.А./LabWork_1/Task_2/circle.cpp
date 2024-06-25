#include "circle.h"

//отрисовка квадрата, в который влазит круг
QRectF Circle::boundingRect() const{
    return {-radius, -radius, radius * 2, radius * 2};
}


void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);
    painter->drawEllipse(int(-radius/2), int(-radius/2), int(radius), int(radius));

};

qreal Circle::countPerimeter(){
    qreal perimeter = radius * 2 * M_PI;
    return perimeter;
}

qreal Circle::countSquare(){
    return radius * radius * M_PI;
}


qreal Circle::newSquare(qreal con){
   return radius += con;
}

void Circle::setParameters(qreal param1, qreal  /*param2*/, qreal  /*param3*/){
    radius = param1;
}



















