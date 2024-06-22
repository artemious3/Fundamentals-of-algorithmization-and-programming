#include "S_scene.h"

S_Scene::S_Scene()
    : bestScore(0),
      scoreTextItem(nullptr),
      inGame(false),
      gameOverPicture(nullptr) {

  scoreTextItem = new QGraphicsTextItem();
  gameOverPicture = new QGraphicsPixmapItem();
}

void S_Scene::addSnake() {
  snake = new Snake;
  for (auto i : snake->snakeBody) {
    addItem(i);
  }
}

void S_Scene::startGame() {

  addSnake();
  addApple();
  inGame = true;
  score = 0;
  timer = new QTimer();
  connect(timer, &QTimer::timeout, [=]() {
    moveSnake();
    checkCollisisons();
    updateScoreText();
    if (snake->getDir() == none) {
      gameOver();
      inGame = false;
    }
  });

  timer->start(TIME);

  scoreTextItem->show();
  QFont mFont("Consolas", FONT_HIGH, QFont::Bold);
  scoreTextItem->setFont(mFont);
  scoreTextItem->setDefaultTextColor(Qt::red);
  scoreTextItem->setPos(TEXT_POINT);
  addItem(scoreTextItem);

  if (gameOverPicture) {
    removeItem(gameOverPicture);
  }
}

bool S_Scene::getInGame() const {
  return inGame;
}

void S_Scene::setInGame(bool value) {
  inGame = value;
}

void S_Scene::addApple() {
  apple = new Apple;
  addItem(apple);
}

void S_Scene::checkCollisisons() {

  QList<QGraphicsItem*> itemsList = items();
  for (QGraphicsItem* item : itemsList) {
    if (dynamic_cast<Apple*>(item) &&
        item->collidesWithItem(snake->snakeBody[0])) {
      removeItem(item);
      ++score;
      addApple();
      snake->increaseSnake();
      addItem(snake->snakeBody.last());
      delete item;
      item = nullptr;
    }
  }
}

void S_Scene::gameOver() {

  snakeScoreValue = score;
  emit snakeGameOverSignal();
  gameOverPicture->setPixmap(
      QPixmap(":/Images/gameover.png")
          .scaled(QSize(GAME_OVER_SIZE, GAME_OVER_SIZE)));
  gameOverPicture->setPos(int(SCENE_RECT / 4), int(SCENE_RECT / 4));
  addItem(gameOverPicture);

  for (auto& i : snake->snakeBody) {
    removeItem(i);
  }

  scoreTextItem->hide();
  removeItem(apple);
  delete snake;
  delete timer;
  delete apple;
  snake = nullptr;
  timer = nullptr;
  apple = nullptr;
}

void S_Scene::updateScoreText() {
  // Отображаем счет
  bestScore = score > bestScore ? score : bestScore;
  QString htmlString = "<p> Score: " + QString::number(score) + "</p>" +
                       "<p> Best score: " + QString::number(bestScore) + "</p>";
  scoreTextItem->setHtml(htmlString);
}

void S_Scene::moveSnake() {
  snake->move();
}

void S_Scene::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Left && snake->getDir() != rightTurn) {
    snake->setDir(leftTurn);
  } else if (key == Qt::Key_Right && snake->getDir() != leftTurn) {
    snake->setDir(rightTurn);
  } else if (key == Qt::Key_Up && snake->getDir() != down) {
    snake->setDir(up);
  } else if (key == Qt::Key_Down && snake->getDir() != up) {
    snake->setDir(down);
  }
}
