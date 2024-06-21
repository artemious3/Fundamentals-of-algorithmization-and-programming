#include "F_player.h"

Player::Player(QPixmap pixmap){
  setPixmap(pixmap.scaled(QSize(CAT_SIZE, CAT_SIZE), Qt::KeepAspectRatio));
  setPos(int(SC_RECT / 2), CAT_LEVEL);
}

void Player::moveLeft() {
  if (currentDirection != Directions::Left) {
    currentDirection = Directions::Left;
    setPixmap(QPixmap(":/Images/cat left.png")
                  .scaled(QSize(CAT_SIZE, CAT_SIZE), Qt::KeepAspectRatio));
  }
  if (x() > 0) {  // Проверяем, не достиг ли кот левой границы сцены
    setX(x() - SHIFT);  // Двигаем кота влево
  }
}

void Player::moveRight() {

  if (currentDirection != Directions::Right) {
    currentDirection = Directions::Right;
    setPixmap(QPixmap(":/Images/cat right.png")
                  .scaled(QSize(CAT_SIZE, CAT_SIZE), Qt::KeepAspectRatio));
  }
  if (x() + CAT_SIZE <
      SC_RECT) {  // Проверяем, не достиг ли кот правой границы сцены
    setX(x() + SHIFT);  // Двигаем кота вправо
  }
}

void Player::stand() {
  if (currentDirection != Directions::None) {
    currentDirection = Directions::None;
    setPixmap(QPixmap(":/Images/cat sitting.png")
                  .scaled(QSize(CAT_SIZE, CAT_SIZE), Qt::KeepAspectRatio));
  }
}
