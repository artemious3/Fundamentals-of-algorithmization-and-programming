#ifndef F_SCENE_H
#define F_SCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QObject>
#include <QString>
#include <QTimer>

#include "F_fruits.h"
#include "F_player.h"
#include "globals.h"

class F_Scene : public QGraphicsScene {
  Q_OBJECT
 public:
  F_Scene();
  void addPlayerAndTextItems();
  void keyPressEvent(QKeyEvent* event) override;
  void startGame();
  bool getInGame() const;
  void setInGame(bool value);

 signals:
  void foodCatcherGameOverSignal();

 private:
  QTimer* fruitGeneratorTimer;
  QTimer* checkCollisionsTimer;
  QGraphicsTextItem* scoreTextItem;
  QGraphicsTextItem* timerText;
  Player* cat;
  void setUpFruitTimer();
  void setUpCollisionsTimer();
  void checkCollisions();
  void gameOver();
  void updateTimerText();
  void updateScoreText();
  int score;
  int gameTime;
  int bestScore;
  bool inGame;

 private slots:
  void generateFruit();
};

#endif  // F_SCENE_H
