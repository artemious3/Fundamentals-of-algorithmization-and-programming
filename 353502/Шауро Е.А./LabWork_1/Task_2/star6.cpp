#include "star6.h"


QRectF Star6::boundingRect() const{
    qreal outerRadius = coef > 1? radius * coef: radius ;
    return {-outerRadius, -outerRadius, outerRadius * 2, outerRadius * 2};
}


void Star6::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    QPolygonF starPolygon;

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    for (int i = 0; i < 12; ++i) {
        qreal angle = i * M_PI / 6 - M_PI / 2;
        qreal radius = (i % 2 == 0) ? outerRadius : innerRadius;
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        starPolygon << point;
}
    painter->drawPolygon(starPolygon);
}


qreal Star6::countPerimeter(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/6));
    qreal perimeter = length * 12;
    return perimeter;
}

qreal Star6::countSquare(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/3));
    qreal length2 = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/6));

    qreal area = length2 / 4 * sqrt(4 * length * length - length2 * length2) * 6;
    qreal figure = 6 * length2 * length2 / (4 * tan(M_PI / 6));
    return area + figure;

}

qreal Star6::newSquare(qreal con){
    return radius += con;
}

void Star6::setParameters(qreal param1, qreal param2, qreal  /*param3*/){
    radius = param1;
    coef = param2 / param1;
}



