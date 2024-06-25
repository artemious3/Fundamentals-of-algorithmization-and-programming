#include "standart.h"


Standart::Standart(){
    setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemSendsGeometryChanges);
    connect(this, &Standart::positionChanged, this, &Standart::updatePosLabel);
    connect(this, &Standart::perimeterChanged, this, &Standart::updatePerimeterLabel);
    connect(this, &Standart::squareChanged, this, &Standart::updateSquareLabel);
}



void Standart::mousePressEvent(QGraphicsSceneMouseEvent * /*event*/){
    this->setCursor(QCursor(Qt::ClosedHandCursor));

}
void Standart::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
   this->setPos(mapToScene(event->pos()));

}
void Standart::mouseReleaseEvent(QGraphicsSceneMouseEvent * /*event*/){
    this->setCursor(QCursor(Qt::ArrowCursor));

}

void Standart::updatePosLabel(const QPointF &center){
    emit positionUpdated(center);
}

void Standart::updatePerimeterLabel(qreal perimetr){
    emit perimeterUpdated(perimetr);
}
void Standart::updateSquareLabel(qreal square){
    emit squareUpdated(square);
}



QVariant Standart::itemChange(GraphicsItemChange change, const QVariant &value){

    if (change == QGraphicsItem::ItemPositionHasChanged){
        QPointF center = scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2);
        emit positionChanged(center);
    }
    return QGraphicsItem::itemChange(change, value);
}



QRectF Standart::boundingRect() const{
    return {};
}

void Standart::moveFigureTo(double newX, double newY)
{
    // Переместить центр масс фигуры в новую точку (newX, newY)
    QPointF currentCenter = scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2);
    QPointF newPoint(newX - currentCenter.x(), newY - currentCenter.y());
    setPos(pos() + newPoint);

    emit positionChanged(scenePos() + QPointF(boundingRect().width() / 2, boundingRect().height() / 2));
}


qreal Standart::countPerimeter(){
}

qreal Standart::countSquare(){

}

qreal Standart::newSquare(qreal con){

}

void Standart::setParameters(qreal param1, qreal param2, qreal param3){

}
void Standart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

}
