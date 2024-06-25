#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>

#include "B_const.h"

class BirdItem : public QWidget, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit BirdItem(QPixmap pixmap);

    qreal y() const;
    qreal rotation() const;
    void shootUp();
    void startFlying();
    void freezeInPlaace();

signals:

public slots:
    void setY(qreal y);
    void setRotation(qreal rotation);
    void rotateTo(const qreal& end, const int& duration, const QEasingCurve& curve);
    void fallToTheGround();

private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();
    WingPosition wingPosition;
    bool wingDirection; // 0 - вниз, 1 - вверх
    qreal m_y;
    qreal m_rotation;
    qreal groundPosition;
    QPropertyAnimation *yAnimation;
    QPropertyAnimation *rotationAnimation;
};

#endif // BIRDITEM_H
