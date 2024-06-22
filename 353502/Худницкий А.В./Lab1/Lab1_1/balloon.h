#ifndef BALLOON_H
#define BALLOON_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Balloon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Balloon(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void moveUp();
    void explode();

private:
    qreal currentHeight;
    QTimer *timer;
};

#endif // BALLOON_H
