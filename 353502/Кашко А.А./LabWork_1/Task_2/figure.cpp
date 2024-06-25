#include "figure.h"

Base::Base() {
    setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemSendsGeometryChanges);
    connect(this, &Base::squareChanged, this, &Base::updateSquareLabel);
    connect(this, &Base::perimeterChanged, this, &Base::updatePerimeterLabel);
    connect(this, &Base::positionChanged, this, &Base::updatePosLabel);
}

QRectF Base::boundingRect()const {
    return QRectF();
}

void Base::moveFigureTo(qreal x, qreal y) {

    // Переместить центр масс фигуры в новую точку (newX, newY)
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

void Base::updateSquareLabel(qreal square){
    emit squareUpdated(square);
}

void Base::updatePosLabel(const QPointF &center){
    emit positionUpdated(center);
}

void Base::updatePerimeterLabel(qreal perimetr){
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

qreal Base::Perimeter() {}

qreal Base::Area() {}

qreal Base::newArea(qreal number) {}

void Base::newparametrs(double side_1, double side_2, double side_3) {}
