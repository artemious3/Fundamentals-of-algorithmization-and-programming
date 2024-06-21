#include "rhombus.h"

QRectF Rhombus::boundingRect() const{
    qreal diagonalLength1 = base * coef;
    qreal diagonalLength2 = base;
    return {-diagonalLength1 / 2, -diagonalLength2 / 2, diagonalLength1, diagonalLength2};
}


void Rhombus::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    QPolygonF rhombusPolygon;

    QPointF center(0, 0);

    qreal diagonalLength1 = base * coef;
    qreal diagonalLength2 = base;

    QPointF point1(center.x() + diagonalLength1 / 2, center.y());
    QPointF point2(center.x(), center.y() - diagonalLength2 / 2);
    QPointF point3(center.x() - diagonalLength1 / 2, center.y());
    QPointF point4(center.x(), center.y() + diagonalLength2 / 2);

    rhombusPolygon << point1 << point2 << point3 << point4;

    painter->drawPolygon(rhombusPolygon);

};

qreal Rhombus::countPerimeter(){
    qreal diagonalLength1 = base * coef;
    qreal diagonalLength2 = base;
    qreal perimeter = sqrt(diagonalLength1 / 2 * diagonalLength1 / 2 + diagonalLength2 / 2 * diagonalLength2 / 2) * 4;
    return perimeter;
}

qreal Rhombus::countSquare(){
    qreal diagonalLength1 = base * coef;
    qreal diagonalLength2 = base;
    return  diagonalLength1 * diagonalLength2 / 2;
}


qreal Rhombus::newSquare(qreal con){
    return base += con;

}
void Rhombus::setParameters(qreal param1, qreal param2, qreal  /*param3*/){
    base = param1;
    coef = param2 / param1;
}
