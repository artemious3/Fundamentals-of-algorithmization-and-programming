#ifndef FRUITS_H
#define FRUITS_H

#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QRandomGenerator>
#include <QPropertyAnimation>

#include "F_const.h"
#include "F_scene.h"

class Fruits :  public  QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Fruits();
    ~Fruits() override;

    qreal y() const;

public slots:
    void setY(qreal y);
    void freezeFruits();

private:
    qreal m_y;
    QPropertyAnimation* yAnimation;
    int xPos;
    static void initializeFruitsTypes();
};

#endif  // FRUITS_H
