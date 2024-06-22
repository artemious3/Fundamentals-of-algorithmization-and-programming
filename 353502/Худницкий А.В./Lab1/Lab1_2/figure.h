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
    Base();
    QRectF boundingRect() const override;
    virtual qreal Area();
    virtual qreal Perimeter();
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
    void updatePos(const QPointF &center);
    void updateSquare(qreal square);
    void updatePerimeter(qreal perimeter);

    void moveFigureTo(qreal x, qreal y);

signals:
    void positionChanged(const QPointF &center);
    void positionUpdated(const QPointF &center);

    void squareChanged(qreal square);
    void squareUpdated(qreal square);

    void perimeterChanged(qreal perimeter);
    void perimeterUpdated(qreal perimeter);

};

#endif // FIGURE_H
