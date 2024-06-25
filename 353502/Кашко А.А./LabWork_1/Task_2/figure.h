#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QObject>
#include <cmath>
#include <QTimer>

class Base : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    //ограничивающий мою фигуу прямоугольник
    Base();
    QRectF boundingRect() const override;
    virtual qreal Perimeter();
    virtual qreal Area();
    virtual qreal newArea(qreal number);
    virtual void newparametrs(double side_1, double side_2, double side_3);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

public slots:
    void updateSquareLabel(qreal square);
    void updatePerimeterLabel(qreal perimeter);
    void updatePosLabel(const QPointF &center);
    void moveFigureTo(qreal x, qreal y);

signals:
    void squareChanged(qreal square);
    void squareUpdated(qreal square);

    void positionChanged(const QPointF &center);
    void positionUpdated(const QPointF &center);

    void perimeterChanged(qreal perimeter);
    void perimeterUpdated(qreal perimeter);

};

#endif // FIGURE_H
