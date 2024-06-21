#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include "F_const.h"

enum Directions { None, Left, Right };

class Player : public QObject, public QGraphicsPixmapItem {
 public:
  explicit Player(QPixmap pixmap);
  void moveLeft();
  void moveRight();
  void stand();

  Directions currentDirection;
};

#endif  // PLAYER_H
