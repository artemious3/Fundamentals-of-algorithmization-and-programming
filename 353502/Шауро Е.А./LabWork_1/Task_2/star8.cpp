#include "star8.h"


QRectF Star8::boundingRect() const{

    qreal outerRadius = coef > 1? radius * coef: radius ;
    return {-outerRadius, -outerRadius, outerRadius * 2, outerRadius * 2};
}


void Star8::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    QPolygonF starPolygon;

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    for (int i = 0; i < 16; ++i) {
        qreal angle = i * M_PI / 8 - M_PI / 2;
        qreal radius = (i % 2 == 0) ? outerRadius : innerRadius;
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        starPolygon << point;
}
painter->drawPolygon(starPolygon);
}


qreal Star8::countPerimeter(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/8));
    qreal perimeter = length * 16;
    return perimeter;
}

qreal Star8::countSquare(){

    qreal innerRadius = radius;
    qreal outerRadius = radius * coef;

    qreal length = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/4));
    qreal length2 = sqrt(innerRadius * innerRadius + outerRadius * outerRadius - 2 * outerRadius * innerRadius * cos (M_PI/8));

    qreal area = length2 / 4 * sqrt(4 * length * length - length2 * length2) * 8;
    qreal figure = 8 * length2 * length2 / (4 * tan(M_PI / 8));
    return area + figure;

}



qreal Star8::newSquare(qreal con){
    return radius += con;
}

void Star8::setParameters(qreal param1, qreal param2, qreal  /*param3*/){
    radius = param1;
    coef = param2 / param1;
}



