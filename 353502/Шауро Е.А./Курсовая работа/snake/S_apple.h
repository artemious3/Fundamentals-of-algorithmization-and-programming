#ifndef APPLE_H
#define APPLE_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QRandomGenerator>

#include "S_const.h"

class Apple : public QObject, public QGraphicsPixmapItem
{
public:
    Apple();
};

#endif // APPLE_H
