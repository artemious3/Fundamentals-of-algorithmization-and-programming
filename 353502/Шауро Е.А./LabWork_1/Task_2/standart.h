#ifndef STANDART_H
#define STANDART_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QObject>
#include <cmath>


class Standart : public QObject , public QGraphicsItem
{
    Q_OBJECT

public:
    Standart();
    QRectF boundingRect() const override;
    virtual qreal countPerimeter();
    virtual qreal countSquare();
    virtual qreal newSquare(qreal con);
    virtual void setParameters(qreal param1, qreal param2, qreal param3);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;


public slots:
    void updatePosLabel(const QPointF &center);
    void updatePerimeterLabel(qreal perimeter);
    void updateSquareLabel(qreal square);
    void moveFigureTo(double newX, double newY);


signals:
    void positionChanged(const QPointF &center);
    void positionUpdated(const QPointF &center);

    void squareChanged(qreal square);
    void squareUpdated(qreal square);

    void perimeterChanged(qreal perimeter);
    void perimeterUpdated(qreal perimeter);

};

#endif // STANDART_H
