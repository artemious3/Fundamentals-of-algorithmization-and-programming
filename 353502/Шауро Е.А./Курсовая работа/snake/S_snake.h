#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "S_const.h"

class Snake : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT

 public:
  explicit Snake();
  void move();
  void increaseSnake();
  void setDir(const Direction& value);
  Direction getDir() const;

  ~Snake() override;

  QList<QGraphicsPixmapItem*> snakeBody;

 private:
  int snakeLength;
  Direction direction;
};
#endif  // SNAKE_H
