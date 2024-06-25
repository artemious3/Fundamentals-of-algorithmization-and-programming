#include "star5.h"


QRectF Star5::boundingRect() const{
    qreal outerRadius = coef > 1? radius * coef: radius ;
    return {-outerRadius, -outerRadius, outerRadius * 2, outerRadius * 2};
}


void Star5::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    QPolygonF starPolygon;

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    for (int i = 0; i < 10; ++i) {
        qreal angle = i * 2.0 * M_PI / 10 - M_PI / 2;
        qreal radius = (i % 2 == 0) ? outerRadius : innerRadius;
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        starPolygon << point;
}
    painter->drawPolygon(starPolygon);
}


qreal Star5::countPerimeter(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/10));
    qreal perimeter = length * 10;
    return perimeter;
}

qreal Star5::countSquare(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/5));
    qreal length2 = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/10));

    qreal area = length2 / 4 * sqrt(4 * length * length - length2 * length2) * 5;
    qreal figure = 5 * length2 * length2 / (4 * tan(M_PI / 5));
    return area + figure;

}

qreal Star5::newSquare(qreal con){
    return radius += con;
}

void Star5::setParameters(qreal param1, qreal param2, qreal  /*param3*/){
    radius = param1;
    coef = param2 / param1;
}



