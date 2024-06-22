#include "figure.h"

Base::Base() {
    setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemSendsGeometryChanges);
    connect(this, &Base::squareChanged, this, &Base::updateSquare);
    connect(this, &Base::perimeterChanged, this, &Base::updatePerimeter);
    connect(this, &Base::positionChanged, this, &Base::updatePos);
}

QRectF Base::boundingRect()const {
    return QRectF();
}

void Base::moveFigureTo(qreal x, qreal y) {

    QPointF currentCenter = scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2);
    QPointF displacement(x - currentCenter.x(), y - currentCenter.y());
    setPos(pos() + displacement);

    emit positionChanged(scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2));
}



void Base::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) {}

void Base::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    this->setPos(mapToScene(event->pos()));
}

void Base::mousePressEvent(QGraphicsSceneMouseEvent *event) {}

void Base::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {}

void Base::updatePos(const QPointF &center){
    emit positionUpdated(center);
}

void Base::updateSquare(qreal square){
    emit squareUpdated(square);
}

void Base::updatePerimeter(qreal perimetr){
    emit perimeterUpdated(perimetr);
}

QVariant Base::itemChange(GraphicsItemChange change, const QVariant &value){

    if (change == QGraphicsItem::ItemPositionHasChanged){
        QPointF center = scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2);
        emit positionChanged(center);
    }

    if(change == QGraphicsItem::ItemSelectedChange){
        qreal square = Area();
        emit squareChanged(square);
    }
    return QGraphicsItem::itemChange(change, value);
}

qreal Base::Area() {}

qreal Base::Perimeter() {}

qreal Base::newArea(qreal number) {}

void Base::newparametrs(double side_1, double side_2, double side_3) {}
