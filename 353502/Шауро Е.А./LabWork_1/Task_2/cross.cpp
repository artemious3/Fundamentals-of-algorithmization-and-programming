#include "cross.h"

QRectF Cross::boundingRect() const{
    qreal lenVert = lenHor * coef;
    return {-width/2 - lenHor, -width/2 - lenVert, width + lenHor * 2, width + lenVert * 2};
}


void Cross::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    qreal lenVert = lenHor * coef;

    QPointF p1(-width/2, width/2);
    QPointF p2(-width/2, width/2 + lenVert);
    QPointF p3(width/2, width/2 + lenVert);
    QPointF p4(width/2, width/2);
    QPointF p5(width/2 + lenHor, width/2);
    QPointF p6(width/2 + lenHor, -width/2);
    QPointF p7(width/2, -width/2);
    QPointF p8(width/2, -width/2 - lenVert);
    QPointF p9(-width/2, -width/2 - lenVert);
    QPointF p10(-width/2, -width/2);
    QPointF p11(-width/2 - lenHor, -width/2);
    QPointF p12(-width/2 - lenHor, width/2);


    QPolygonF cross;
    cross << p1 << p2 << p3 << p4 << p5 << p6 << p7 << p8 << p9  << p10 << p11<< p12;
    painter->drawPolygon(cross);
}

qreal Cross::countPerimeter(){

    qreal lenVert = lenHor * coef;
    qreal perimeter = width * 4 + lenHor * 4 + lenVert * 4;
    return perimeter;
}

qreal Cross::countSquare(){

    qreal lenVert = lenHor * coef;
    qreal square = width * (2 * lenVert + width) + width * 2 * lenHor;
    return square;

}



qreal Cross::newSquare(qreal con){
    return lenHor += con;
}

void Cross::setParameters(qreal param1, qreal param2, qreal param3){
   lenHor = param1;
   coef = param2 / param1;
   width = param3;
}

























