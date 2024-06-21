#ifndef B_SCENE_H
#define B_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "B_birditem.h"
#include "B_pillaritem.h"
#include "globals.h"

class B_Scene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit B_Scene(QObject* parent = nullptr);
  void addBird();
  void startGame();
  void incrementScore();
  int getScore() const;
  void showGameOver();

signals:
  void birdGameOverSignal();

 private:
  void hideGameOver();
  void cleanPillars();
  void setUpPillarTimer();
  void freeze();

  QTimer* pillarTimer;
  BirdItem* bird;
  bool gameOn;
  bool isFirstSet;
  int score;
  int bestScore;

  QGraphicsPixmapItem* gameOverPix;
  QGraphicsTextItem* scoreTextItem;

 protected:
  void keyPressEvent(QKeyEvent* event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // B_SCENE_H
