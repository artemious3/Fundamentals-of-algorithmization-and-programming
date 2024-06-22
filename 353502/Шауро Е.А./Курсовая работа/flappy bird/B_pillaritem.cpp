#include "B_pillaritem.h"

PillarItem::PillarItem()
    : topPillar(new QGraphicsPixmapItem(QPixmap(":/Images/topPillar.png"))),
      bottomPillar(
          new QGraphicsPixmapItem(QPixmap(":/Images/bottomPillar.png"))),
      pastBird(false) {

  topPillar->setPos(QPointF(0, 0) -
                    QPointF(topPillar->boundingRect().width() / 2,
                            topPillar->boundingRect().height() + DUR));
  bottomPillar->setPos(QPointF(0, 0) +
                       QPointF(-bottomPillar->boundingRect().width() / 2, 0));

  addToGroup(topPillar);
  addToGroup(bottomPillar);

  yPos = QRandomGenerator::global()->bounded(Y_RAND);
  int xRandomizer = QRandomGenerator::global()->bounded(X_RAND);
  setPos(QPoint(0, 0) + QPoint(DUR + xRandomizer, yPos));

  xAnimation = new QPropertyAnimation(this, "x", this);
  xAnimation->setStartValue(PIL_START);
  xAnimation->setEndValue(PIL_END);  // то, насколько колонны зайдут за кадр
  xAnimation->setEasingCurve(QEasingCurve::Linear);
  xAnimation->setDuration(PIL_SPEED);  // скорость в мск
  xAnimation->start();

  connect(xAnimation, &QPropertyAnimation::finished, [=]() {
    scene()->removeItem(this);
    delete this;
  });
}

PillarItem::~PillarItem() {
  delete topPillar;
  delete bottomPillar;
}

qreal PillarItem::x() const {
  return m_x;
}

void PillarItem::freezeInPlace() {
  xAnimation->stop();
}

void PillarItem::setX(qreal x) {
  m_x = x;

  if (x < 0 && !pastBird) {
    //флаг, означающий что столбец пройден птицей
    pastBird = true;
    QGraphicsScene* mScene = scene();
    B_Scene* myScene = dynamic_cast<B_Scene*>(mScene);
    if (myScene) {
      myScene->incrementScore();
    }
  }
  if (collidesWithBird()) {
    emit collideFail();
  }
  setPos(QPointF(0, 0) + QPointF(x, yPos));
}

bool PillarItem::collidesWithBird() {
  QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
  collidingItems.append(bottomPillar->collidingItems());

  foreach (QGraphicsItem* item, collidingItems) {
    BirdItem* birdItem = dynamic_cast<BirdItem*>(item);
    if (birdItem) {
      return true;
    }
  }
  return false;
}
