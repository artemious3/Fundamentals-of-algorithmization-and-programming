#include "F_fruits.h"

static QList<QPixmap> fruitsTypes;

Fruits::Fruits() {

  if (fruitsTypes.isEmpty()) {
    initializeFruitsTypes();
  }
  int type = QRandomGenerator::global()->bounded(FRUITS_COUNT - 1);
  setPixmap(fruitsTypes[type].scaled(QSize(FRUITS_SIZE, FRUITS_SIZE),
                                     Qt::KeepAspectRatio));

  xPos = QRandomGenerator::global()->bounded(FRUITS_DOWN_BORD, FRUITS_UP_BORD);
  yAnimation = new QPropertyAnimation(this, "y", this);
  yAnimation->setStartValue(0);  // Начальная позиция за кадром
  yAnimation->setEndValue(SIDE);  // Конечная позиция внизу экрана
  yAnimation->setEasingCurve(QEasingCurve::Linear);
  yAnimation->setDuration(SPEED);  // Скорость падения в миллисекундах
  yAnimation->start();

  connect(yAnimation, &QPropertyAnimation::finished, [=]() {
    scene()->removeItem(this);
    delete this;
  });
}

void Fruits::setY(qreal y) {
  m_y = y;
  setPos(QPointF(0, 0) + QPointF(xPos, y));
}

void Fruits::freezeFruits() {
  yAnimation->stop();
}

void Fruits::initializeFruitsTypes() {

  fruitsTypes.append(QPixmap(":/Images/apple.png"));
  fruitsTypes.append(QPixmap(":/Images/banana.png"));
  fruitsTypes.append(QPixmap(":/Images/coconut.png"));
  fruitsTypes.append(QPixmap(":/Images/mango.png"));
  fruitsTypes.append(QPixmap(":/Images/orange.png"));
  fruitsTypes.append(QPixmap(":/Images/peach.png"));
  fruitsTypes.append(QPixmap(":/Images/pear.png"));
  fruitsTypes.append(QPixmap(":/Images/pineapple.png"));
  fruitsTypes.append(QPixmap(":/Images/raspberry.png"));
  fruitsTypes.append(QPixmap(":/Images/strawberry.png"));
  fruitsTypes.append(QPixmap(":/Images/watermelon.png"));
  fruitsTypes.append(QPixmap(":/Images/grape.png"));
}

Fruits::~Fruits() {
  delete yAnimation;
  yAnimation = nullptr;
}

qreal Fruits::y() const {
  return m_y;
}
