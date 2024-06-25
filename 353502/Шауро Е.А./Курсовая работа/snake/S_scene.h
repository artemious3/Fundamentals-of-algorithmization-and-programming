#ifndef SCENE_H
#define SCENE_H
#pragma once
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QTimer>

#include "S_apple.h"
#include "S_snake.h"
#include "globals.h"

class S_Scene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit S_Scene();
  void startGame();
  bool getInGame() const;
  void setInGame(bool value);

 signals:
  void snakeGameOverSignal();

 private:
  Apple* apple;
  Snake* snake;
  QTimer* timer;
  QGraphicsTextItem* scoreTextItem;
  QGraphicsPixmapItem* gameOverPicture;
  int score;
  int bestScore;
  bool inGame;
  void moveSnake();
  void addSnake();
  void addApple();
  void checkCollisisons();
  void gameOver();
  void updateScoreText();

 protected:
  void keyPressEvent(QKeyEvent* event) override;
};

#endif  // SCENE_H
