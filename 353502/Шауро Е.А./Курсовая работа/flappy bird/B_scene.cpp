#include "B_scene.h"
#include "mainwindow.h"
B_Scene::B_Scene(QObject* parent)
    : QGraphicsScene(parent),
      gameOn(false),
      score(0),
      bestScore(0),
      gameOverPix(nullptr),
      isFirstSet(true) {
  setUpPillarTimer();
  gameOverPix = new QGraphicsPixmapItem();
}

void B_Scene::addBird() {
  bird = new BirdItem(
      QPixmap(":/Images/bird1.png")
          .scaled(QSize(BIRD_SIZE, BIRD_SIZE), Qt::KeepAspectRatio));
  addItem(bird);
}

void B_Scene::startGame() {
  score = 0;
  bird->startFlying();
  //Pillars
  if (!pillarTimer->isActive()) {
    cleanPillars();
    gameOn = true;
    hideGameOver();
    pillarTimer->start(TIME_INTERVAL);
  }
}

void B_Scene::setUpPillarTimer() {
  pillarTimer = new QTimer(this);
  connect(pillarTimer, &QTimer::timeout, [=]() {
    PillarItem* pillarItem = new PillarItem();
    connect(pillarItem, &PillarItem::collideFail, [=]() {
      pillarTimer->stop();
      freeze();
      gameOn = false;
      showGameOver();
    });
    addItem(pillarItem);
  });
}

void B_Scene::freeze() {
  bird->freezeInPlaace();
  QList<QGraphicsItem*> sceneItems = items();

  foreach (QGraphicsItem* item, sceneItems) {
    PillarItem* pillar = dynamic_cast<PillarItem*>(item);
    if (pillar) {
      pillar->freezeInPlace();
    }
  }
}

int B_Scene::getScore() const {
  return score;
}

void B_Scene::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Space) {
    if (gameOn) {
      bird->shootUp();
    }
  }
  QGraphicsScene::keyPressEvent(event);
}

void B_Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    if (gameOn) {
      bird->shootUp();
    }
  }
  QGraphicsScene::mousePressEvent(event);
}

void B_Scene::incrementScore() {
  score++;
  if (score > bestScore) {
    bestScore = score;
  }
}

void B_Scene::showGameOver() {
  gameOverPix = new QGraphicsPixmapItem(
      QPixmap(":/Images/—Pngtree—orange pixel wind gameover broken_5525880.png")
          .scaled(QSize(GAMEOVER_SIZE, GAMEOVER_SIZE), Qt::KeepAspectRatio));
  addItem(gameOverPix);
  gameOverPix->setPos(QPointF(0, 0) -
                      QPointF(gameOverPix->boundingRect().width() / 2,
                              gameOverPix->boundingRect().height() / 2));

  scoreTextItem = new QGraphicsTextItem();
  QString htmlString = "<p> Score: " + QString::number(score) + "</p>" +
                       "<p> Best score: " + QString::number(bestScore) + "</p>";

  QFont mFont("Consolas", FONT_SIZE, QFont::Bold);
  scoreTextItem->setHtml(htmlString);
  scoreTextItem->setFont(mFont);
  scoreTextItem->setDefaultTextColor(Qt::yellow);
  addItem(scoreTextItem);

  scoreTextItem->setPos(QPointF(0, 0) -
                        QPointF(scoreTextItem->boundingRect().width() / 2,
                                -gameOverPix->boundingRect().height() / 2));

    birdScoreValue = score;
    emit birdGameOverSignal();
}

void B_Scene::hideGameOver() {
  if (isFirstSet) {
    isFirstSet = false;
    return;
  }
  if (gameOverPix) {
    removeItem(gameOverPix);
    delete gameOverPix;
    gameOverPix = nullptr;
  }
  if (scoreTextItem) {
    removeItem(scoreTextItem);
    delete scoreTextItem;
    scoreTextItem = nullptr;
  }
}

void B_Scene::cleanPillars() {
  QList<QGraphicsItem*> sceneItems = items();
  foreach (QGraphicsItem* item, sceneItems) {
    PillarItem* pillar = dynamic_cast<PillarItem*>(item);
    if (pillar) {
      removeItem(pillar);
      delete pillar;
      pillar = nullptr;
    }
  }
}
