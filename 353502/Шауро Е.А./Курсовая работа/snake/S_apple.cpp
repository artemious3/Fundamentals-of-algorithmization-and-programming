#include "S_apple.h"

Apple::Apple() {
  setPixmap(QPixmap(":/Images/appleForSnake.png")
                .scaled(QSize(APPLE_SIZE, APPLE_SIZE), Qt::KeepAspectRatio));
  int x = QRandomGenerator::global()->bounded(APPLE_BORDER, SCENE_RECT - APPLE_BORDER);
  int y = QRandomGenerator::global()->bounded(APPLE_BORDER, SCENE_RECT - APPLE_BORDER);

  setPos(QPointF(x, y));
}

