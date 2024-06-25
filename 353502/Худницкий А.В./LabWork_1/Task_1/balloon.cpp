#include "balloon.h"

#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPropertyAnimation>
#include <QtMath>
#include <QRandomGenerator>

Balloon::Balloon(QObject *parent) : QObject(parent), QGraphicsItem()
{
    currentHeight = 400;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Balloon::moveUp);
    timer->start(6);
}

QRectF Balloon::boundingRect() const
{
    return QRectF(0, 0, 500, 500).translated(250, currentHeight);
}

void Balloon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->drawEllipse(250, currentHeight, 20, 30);
}

void Balloon::moveUp()
{
    currentHeight -= 1;
    if (currentHeight <= 10) {
        explode();
    }

    update();
}

void Balloon::explode()
{
    timer->stop();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    const int numParticles = 50;
    for (int i = 0; i < numParticles; ++i) {
        qreal angle = (qrand() % 360) * 3.14 / 180.0;
        qreal radius = qrand() % 20;
        qreal x = radius * qCos(angle);
        qreal y = radius * qSin(angle);
        QGraphicsEllipseItem *particle = new QGraphicsEllipseItem(250, 10, 4, 4);
        particle->setPos(x, y - currentHeight);
        particle->setBrush(Qt::yellow);
        scene()->addItem(particle);

    }

    scene()->removeItem(this);
    delete this;

}
