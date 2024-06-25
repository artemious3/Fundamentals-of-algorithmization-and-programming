#include "square.h"

QRectF Square::boundingRect() const{
    return {-sideLength / 2, -sideLength / 2, sideLength, sideLength};
}


void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){

    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);
    painter->drawRect(int(-sideLength / 2), int(-sideLength / 2), int(sideLength), int(sideLength));

};

qreal Square::countPerimeter(){
    qreal perimeter = sideLength * 4;
    return perimeter;
}

qreal Square::countSquare(){
    return sideLength * sideLength;
}

qreal Square::newSquare(qreal con){
    return sideLength += con;
}

void Square::setParameters(qreal param1, qreal  /*param2*/, qreal  /*param3*/){
    sideLength = param1;
}





















