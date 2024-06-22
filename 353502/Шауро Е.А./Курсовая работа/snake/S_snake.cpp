#include "S_snake.h"

Snake::Snake() : snakeLength(4), direction(Direction::rightTurn) {
  for (int i = 0; i < snakeLength; ++i) {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
    QPixmap pixmap;
    if (i == 0) {
      pixmap = QPixmap(":/Images/skin.png");
    }

    else {
      pixmap = QPixmap(":/Images/skin.png");
    }

    item->setPixmap(
        (pixmap).scaled(QSize(SNAKE_SIZE, SNAKE_SIZE), Qt::KeepAspectRatio));
    item->setPos((snakeLength - i - 1) * STEP, 0);
    snakeBody.append(item);
  }
}

void Snake::move() {
  // Получаем границы сцены
  QRectF sceneRect = QRectF(0, 0, SCENE_RECT, SCENE_RECT);

  for (int i = snakeBody.size() - 1; i > 0; --i) {
    if (!sceneRect.contains(snakeBody[i - 1]->pos())) {
      return;
    }
    snakeBody[i]->setPos(snakeBody[i - 1]->pos());
  }

  switch (direction) {
    case leftTurn:
      if (snakeBody[0]->x() - STEP >= sceneRect.left()) {
        snakeBody[0]->setPos(snakeBody[0]->x() - STEP, snakeBody[0]->y());
        direction = leftTurn;
      } else {
        direction = none;
      }
      break;
    case rightTurn:
      if (snakeBody[0]->x() + STEP <= sceneRect.right()) {
        snakeBody[0]->setPos(snakeBody[0]->x() + STEP, snakeBody[0]->y());
        direction = rightTurn;
      } else {
        direction = none;
      }
      break;
    case up:
      if (snakeBody[0]->y() - STEP >= sceneRect.top()) {
        snakeBody[0]->setPos(snakeBody[0]->x(), snakeBody[0]->y() - STEP);
        direction = up;
      } else {
        direction = none;
      }
      break;
    case down:
      if (snakeBody[0]->y() + STEP <= sceneRect.bottom()) {
        snakeBody[0]->setPos(snakeBody[0]->x(), snakeBody[0]->y() + STEP);
        direction = down;
      } else {
        direction = none;
      }
      break;
    case none:
      direction = none;
      break;
  }

  // Проверяем, не столкнулась ли голова с телом
  for (int i = 1; i < snakeLength; ++i) {
    if (snakeBody[0]->collidesWithItem(snakeBody[i])) {
      direction = none;
      return;
    }
  }
}

void Snake::increaseSnake() {
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(
      QPixmap(":/Images/skin.png")
          .scaled(QSize(SNAKE_SIZE, SNAKE_SIZE), Qt::KeepAspectRatio));
  item->setPos(snakeBody.last()->pos());
  snakeBody.append(item);
  ++snakeLength;
}

Direction Snake::getDir() const {
  return direction;
}

void Snake::setDir(const Direction& value) {
  direction = value;
}

Snake::~Snake() {
  for (auto& i : snakeBody) {
    delete i;
    i = nullptr;
  }
}
