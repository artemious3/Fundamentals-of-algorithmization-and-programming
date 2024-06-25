#include "triangle.h"

//отрисовка квадрата, в который влазит треугольник
QRectF Triangle::boundingRect() const{
    return {-sideLength/2 - 10, -sideLength/2 - 10 , sideLength + 15, sideLength + 20};
}


void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    QPolygonF  TrianglePolygon;

    QPointF center(0, 0);

    QPointF point1(center.x(), center.y() - sqrt(3.0) / 3 * sideLength);
    QPointF point2(center.x() + sideLength / 2, center.y() + sqrt(3.0) / 6 * sideLength);
    QPointF point3(center.x() - sideLength / 2, center.y() + sqrt(3.0) / 6 * sideLength);

   TrianglePolygon << point1 << point2 << point3;

   painter->drawPolygon(TrianglePolygon);
};


qreal Triangle::countPerimeter(){
    qreal perimeter = sideLength * 3;
    return perimeter;
}

qreal Triangle::countSquare(){
    return sideLength * sideLength * sqrt(3.0) / 4;
}


qreal Triangle::newSquare(qreal con){
   return sideLength += con;
}


void Triangle::setParameters(qreal param1, qreal  /*param2*/, qreal  /*param3*/){
    sideLength = param1;
}




















