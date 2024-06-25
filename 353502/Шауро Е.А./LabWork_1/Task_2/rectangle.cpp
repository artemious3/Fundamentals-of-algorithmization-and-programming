#include "rectangle.h"

QRectF Rectangle::boundingRect() const{
    qreal width = base;
    qreal height = base * coef;
    return { -height / 2, -width / 2, height, width};
}


void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);

    qreal width = base;
    qreal height = base * coef;
    painter->drawRect(int(-height / 2), int(-width / 2), int(height), int(width));

};

qreal Rectangle::countPerimeter(){

    qreal width = base;
    qreal height = base * coef;

    qreal perimeter = width * 2 + height * 2;
    return perimeter;
}

qreal Rectangle::countSquare(){
    return base * base * coef * coef;
}



qreal Rectangle::newSquare(qreal con){
    return base += con;
}

void Rectangle::setParameters(qreal param1, qreal param2, qreal  /*param3*/){
    base = param1;
    coef = param2 / param1;
}



















