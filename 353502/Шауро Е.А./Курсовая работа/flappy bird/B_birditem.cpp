#include "B_birditem.h"

BirdItem::BirdItem(QPixmap pixmap)
    : wingPosition(WingPosition::Up), wingDirection(false) {
  setPixmap(pixmap);
  QTimer* birdWingsTimer = new QTimer(this);

  connect(birdWingsTimer, &QTimer::timeout, [=]() { updatePixmap(); });
  birdWingsTimer->start(WINGS_TIMER);

  groundPosition = scenePos().y() + DUR + BIRD_SIZE;

  yAnimation = new QPropertyAnimation(this, "y", this);
  yAnimation->setStartValue(scenePos().y());
  yAnimation->setEndValue(groundPosition);
  yAnimation->setEasingCurve(QEasingCurve::InQuad);
  yAnimation->setDuration(TIME_INTERVAL);
  rotationAnimation = new QPropertyAnimation(this, "rotation", this);
}

qreal BirdItem::rotation() const {
  return m_rotation;
}

qreal BirdItem::y() const {
  return m_y;
}

void BirdItem::shootUp() {

  freezeInPlaace();
  qreal curPosY = y();
  yAnimation->setStartValue(curPosY);
  yAnimation->setEndValue(curPosY - scene()->sceneRect().height() / PART);
  yAnimation->setEasingCurve(QEasingCurve::OutQuad);
  yAnimation->setDuration(MOVE_UP_TIME);

  connect(yAnimation, &QPropertyAnimation::finished,
          [=]() { fallToTheGround(); });
  yAnimation->start();
  rotateTo(MOVE_UP_ANGLE, MOVE_UP_TIME, QEasingCurve::OutCubic);
}

void BirdItem::startFlying() {
  yAnimation->start();
  rotateTo(STR_ANGLE, MOVE_DOWN_TIME, QEasingCurve::InQuad);
}

void BirdItem::freezeInPlaace() {
  yAnimation->stop();
  rotationAnimation->stop();
}

void BirdItem::setY(qreal y) {
  moveBy(0, y - m_y);
  m_y = y;
}

void BirdItem::setRotation(qreal rotation) {
  m_rotation = rotation;
  QPointF center = boundingRect().center();
  QTransform t;
  t.translate(center.x(), center.y());
  t.rotate(rotation);
  t.translate(-center.x(), center.y());
  setTransform(t);
}

void BirdItem::rotateTo(const qreal& end, const int& duration,
                        const QEasingCurve& curve) {
  rotationAnimation->setStartValue((rotation()));
  rotationAnimation->setEndValue(end);
  rotationAnimation->setEasingCurve(curve);
  rotationAnimation->setDuration(duration);
  rotationAnimation->start();
}

void BirdItem::fallToTheGround() {
  if (y() < groundPosition) {
    rotationAnimation->stop();
    yAnimation->setStartValue(y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(MOVE_DOWN_TIME);
    yAnimation->start();
    rotateTo(STR_ANGLE, MOVE_DOWN_TIME, QEasingCurve::InCubic);
  }
}

void BirdItem::updatePixmap() {
  QPixmap pixmap;
  if (wingPosition == Middle) {
    // Если летит вверх
    if (wingDirection) {
      pixmap = QPixmap(":/Images/bird0.png");
      wingPosition = Up;
      wingDirection = false;

    } else {
      pixmap = QPixmap(":/Images/bird2.png");
      wingPosition = Down;
      wingDirection = true;
    }
    setPixmap(
        (pixmap).scaled(QSize(BIRD_SIZE, BIRD_SIZE), Qt::KeepAspectRatio));
  } else {
    wingPosition = Middle;
  }
}

