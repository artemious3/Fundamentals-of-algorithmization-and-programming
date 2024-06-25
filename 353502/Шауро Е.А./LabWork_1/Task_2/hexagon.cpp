#include "hexagon.h"

QRectF Hexagon::boundingRect() const{
    return {-radius, -radius, radius * 2, radius * 2};
}


void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/){
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);
    QPolygonF hexagonPolygon;

    QPointF center(0, 0);

    for (int i = 0; i < 6; ++i) {
        qreal angle = i * M_PI / 3; // Угол между вершинами
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        hexagonPolygon << point;
    }

    painter->drawPolygon(hexagonPolygon);
}


qreal Hexagon::countPerimeter(){
    qreal perimeter = radius * 7;
    return perimeter;
}

qreal Hexagon::countSquare(){
    return radius * 1.5 * radius * sqrt(3.0);
}


qreal Hexagon::newSquare(qreal con){
   return radius += con;
}

void Hexagon::setParameters(qreal param1, qreal  /*param2*/, qreal  /*param3*/){
    radius = param1;
}
