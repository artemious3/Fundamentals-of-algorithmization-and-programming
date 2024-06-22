#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>

#include "B_birdwind.h"
#include "F_foodcatchwind.h"
#include "M3_match3wind.h"
#include "S_snakewind.h"
#include "globals.h"
#include "mainscene.h"
#include "infowindow.h"


QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

private slots:
  void on_birdGameButton_clicked();

  void on_match3GameButton_clicked();

  void on_snakeGameButton_clicked();

  void on_foodCatchButton_clicked();

  void updateSnakeProgBar();

  void updateMatch3ProgBar();

  void updateBirdProgBar();

  void updateFoodCatchProgBar();

  void on_infoButton_clicked();

private:
  MainScene* mainScene;
  Ui::MainWindow* ui;
  Pet* pet;
  void setCatMood();
  void stopTimers();
  void startTimers();
  void GameOver();
  QTimer* timerSnake;
  QTimer* timerMatch3;
  QTimer* timerFlappyBird;
  QTimer* timerFoodCatcher;
  QTimer* petTimer;
  QPropertyAnimation *animation;
  QGraphicsPixmapItem* gameOverPicture;

public slots:
    void enableWindow();
    void takeNewScoreFromBird();
    void takeNewScoreFromSnake();
    void takeNewScoreFromMatch3();
    void takeNewScoreFromFoodCat();
};
#endif  // MAINWINDOW_H

