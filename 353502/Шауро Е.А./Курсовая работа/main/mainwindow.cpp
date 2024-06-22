#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(HOME_SIZE, HOME_SIZE);
  mainScene = new MainScene();
  mainScene->setSceneRect(START_SC_RECT_X, START_SC_RECT_Y, SC_RECT, SC_RECT);

  QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(
      QPixmap(":/Images/mainBack.jpg")
          .scaled(QSize(HOME_SIZE, HOME_SIZE), Qt::KeepAspectRatio));
  mainScene->addItem(pixItem);
  pixItem->setPos(QPointF(0, 0) -
                  QPointF(pixItem->boundingRect().width() / 2,
                          pixItem->boundingRect().height() / 2));

  ui->graphicsView->setScene(mainScene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  pet = new Pet();
  mainScene->addItem(pet);

  timerSnake = new QTimer(this);
  timerMatch3 = new QTimer(this);
  timerFlappyBird = new QTimer(this);
  timerFoodCatcher = new QTimer(this);
  petTimer = new QTimer(this);

  connect(petTimer, &QTimer::timeout, this, &MainWindow::setCatMood);
  petTimer->start(PET_INTERVAL);

  connect(timerSnake, &QTimer::timeout, this, &MainWindow::updateSnakeProgBar);
  timerSnake->start(SNAKE_INTERVAL);

  connect(timerMatch3, &QTimer::timeout, this,
          &MainWindow::updateMatch3ProgBar);
  timerMatch3->start(MATCH3_INTERVAL);

  connect(timerFlappyBird, &QTimer::timeout, this,
          &MainWindow::updateBirdProgBar);
  timerFlappyBird->start(FLAPPY_BIRD_INTERVAL);

  connect(timerFoodCatcher, &QTimer::timeout, this,
          &MainWindow::updateFoodCatchProgBar);
  timerFoodCatcher->start(FOOD_CATCHER_INTERVAL);
}

MainWindow::~MainWindow() {

  delete pet;
  pet = nullptr;

  delete petTimer;
  petTimer = nullptr;

  delete timerSnake;
  timerSnake = nullptr;

  delete timerMatch3;
  timerMatch3 = nullptr;

  delete timerFlappyBird;
  timerFlappyBird = nullptr;

  delete timerFoodCatcher;
  timerFoodCatcher = nullptr;

  delete mainScene;
  mainScene = nullptr;

  delete animation;
  animation = nullptr;

  delete ui;
}

void MainWindow::on_birdGameButton_clicked() {
  stopTimers();
  BirdWind* bWind = new BirdWind();
  bWind->show();
  this->setEnabled(false);
  connect(bWind, &BirdWind::windowClosed, this,
          [=]() { enableWindow(), startTimers(); });
  connect(bWind, &BirdWind::newScoreFromBird, this,
          &MainWindow::takeNewScoreFromBird);
}

void MainWindow::on_match3GameButton_clicked() {
  stopTimers();
  Match3Wind* matThree = new Match3Wind();
  matThree->show();
  this->setEnabled(false);
  connect(matThree, &Match3Wind::windowClosed, this,
          [=]() { enableWindow(), takeNewScoreFromMatch3(), startTimers(); });
}

void MainWindow::on_snakeGameButton_clicked() {
  stopTimers();
  SnakeWind* snWind = new SnakeWind();
  snWind->show();
  this->setEnabled(false);
  connect(snWind, &SnakeWind::windowClosed, this,
          [=]() { enableWindow(), startTimers(); });
  connect(snWind, &SnakeWind::newScoreFromSnake, this,
          &MainWindow::takeNewScoreFromSnake);
}

void MainWindow::on_foodCatchButton_clicked() {
  stopTimers();
  FoodCatchWind* fCatchWin = new FoodCatchWind();
  fCatchWin->show();
  this->setEnabled(false);
  connect(fCatchWin, &FoodCatchWind::windowClosed, this,
          [=]() { enableWindow(), startTimers(); });
  connect(fCatchWin, &FoodCatchWind::newScoreFromFoodCat, this,
          &MainWindow::takeNewScoreFromFoodCat);
}

void MainWindow::on_infoButton_clicked() {
  InfoWindow* info = new InfoWindow();
  info->show();
}

void MainWindow::updateSnakeProgBar() {
  int currentValue = ui->SnakeProgBar->value();
  if (currentValue > 0) {
    ui->SnakeProgBar->setValue(currentValue - 1);
  }
}

void MainWindow::updateMatch3ProgBar() {
  int currentValue = ui->Match3ProgBar->value();
  if (currentValue > 0) {
    ui->Match3ProgBar->setValue(currentValue - 1);
  }
}

void MainWindow::updateBirdProgBar() {
  int currentValue = ui->BirdProgBar->value();
  if (currentValue > 0) {
    ui->BirdProgBar->setValue(currentValue - 1);
  }
}

void MainWindow::updateFoodCatchProgBar() {
  int currentValue = ui->FoodCatchProgBar->value();
  if (currentValue > 0) {
    ui->FoodCatchProgBar->setValue(currentValue - 1);
  }
}

void MainWindow::setCatMood() {
  int birdValue = ui->BirdProgBar->value();
  int snakeValue = ui->SnakeProgBar->value();
  int m3Value = ui->Match3ProgBar->value();
  int foodValue = ui->FoodCatchProgBar->value();

  if (birdValue >= BEST_STATS && snakeValue >= BEST_STATS &&
      m3Value >= BEST_STATS && foodValue >= BEST_STATS) {

    pet->setMood(Cool);

  } else if (birdValue >= NORMAL_STATS && snakeValue >= NORMAL_STATS &&
             m3Value >= NORMAL_STATS && foodValue >= NORMAL_STATS) {

    pet->setMood(Standart);
  }

  else {
    pet->setMood(Angry);
  }

  if (birdValue == 0 || snakeValue == 0 || m3Value == 0 || foodValue == 0) {

    pet->setMood(GoAway);
    QMessageBox messageBox(QMessageBox::Warning, "Bye-bye!",
                           "The characteristic dropped below zero. The pet "
                           "does not want to talk "
                           "to you and goes to another owner!",
                           QMessageBox::Ok);
    messageBox.exec();
    petTimer->stop();
    stopTimers();
    pet->updateCatIcon();
    animation = new QPropertyAnimation(pet, "pos");
    animation->setDuration(2000);  // продолжительность анимации в миллисекундах
    animation->setStartValue(QPointF(0, 0));
    animation->setEndValue(QPointF(ui->graphicsView->width(), 0));
    animation->start();

    GameOver();
    this->setEnabled(false);
    return;
  }

  pet->updateCatIcon();
}

void MainWindow::stopTimers() {
  timerSnake->stop();
  timerMatch3->stop();
  timerFlappyBird->stop();
  timerFoodCatcher->stop();
}

void MainWindow::startTimers() {
  timerSnake->start();
  timerMatch3->start();
  timerFlappyBird->start();
  timerFoodCatcher->start();
}

void MainWindow::GameOver() {
  gameOverPicture = new QGraphicsPixmapItem(
      QPixmap(":/Images/mainGO.png")
          .scaled(QSize(GAMEOVER_SIZE, GAMEOVER_SIZE), Qt::KeepAspectRatio));
  mainScene->addItem(gameOverPicture);
  gameOverPicture->setPos(
      QPointF(0, 0) - QPointF(gameOverPicture->boundingRect().width() / 2,
                              gameOverPicture->boundingRect().height() / 2));
}

void MainWindow::enableWindow() {
  this->setEnabled(true);
}

void MainWindow::takeNewScoreFromBird() {
  int cur = ui->BirdProgBar->value();
  if (cur + birdScoreValue * BIRD_BONUS >= MAX) {
    ui->BirdProgBar->setValue(MAX);
  } else {
    ui->BirdProgBar->setValue(cur + birdScoreValue * BIRD_BONUS);
  }
}

void MainWindow::takeNewScoreFromSnake() {
  int cur = ui->SnakeProgBar->value();
  if (cur + snakeScoreValue * SNAKE_BONUS >= MAX) {
    ui->SnakeProgBar->setValue(MAX);
  } else {
    ui->SnakeProgBar->setValue(cur + snakeScoreValue * SNAKE_BONUS);
  }
}

void MainWindow::takeNewScoreFromMatch3() {
  int cur = ui->Match3ProgBar->value();
  if (cur + match3ScoreValue * MATCH_BONUS >= MAX) {
    ui->Match3ProgBar->setValue(MAX);
  } else {
    ui->Match3ProgBar->setValue(cur + match3ScoreValue * MATCH_BONUS);
  }
}

void MainWindow::takeNewScoreFromFoodCat() {
  int cur = ui->FoodCatchProgBar->value();
  if (cur + foodCatScoreValue * FOODCAT_BONUS >= MAX) {
    ui->FoodCatchProgBar->setValue(MAX);
  } else {
    ui->FoodCatchProgBar->setValue(cur + foodCatScoreValue * FOODCAT_BONUS);
  }
}
