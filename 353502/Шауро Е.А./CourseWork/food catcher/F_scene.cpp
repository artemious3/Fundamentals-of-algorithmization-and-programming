#include "F_scene.h"

F_Scene::F_Scene() : bestScore(0), scoreTextItem(nullptr), inGame(false) {
  setUpFruitTimer();
  scoreTextItem = new QGraphicsTextItem();
}

void F_Scene::addPlayerAndTextItems() {
  cat = new Player(QPixmap(":/Images/cat sitting.png"));
  addItem(cat);

  // Создаем текстовый элемент для таймера и добавляем его на сцену
  timerText = new QGraphicsTextItem();
  QFont mFont("Consolas", TEXT_FONT_SIZE, QFont::Bold);
  timerText->setFont(mFont);
  timerText->setDefaultTextColor(Qt::red);
  addItem(timerText);
  setUpCollisionsTimer();

  scoreTextItem->setFont(mFont);
  scoreTextItem->setDefaultTextColor(Qt::red);
  scoreTextItem->setPos(TEXT_POS_X, TEXT_POS_Y);
  addItem(scoreTextItem);
}

void F_Scene::generateFruit() {

  Fruits* fruit = new Fruits();
  addItem(fruit);
}


void F_Scene::keyPressEvent(QKeyEvent* event) {
  // Обрабатываем нажатия клавиш
  switch (event->key()) {
    case Qt::Key_Left:
      cat->moveLeft();
      break;
    case Qt::Key_Right:
      cat->moveRight();
      break;
    default:
      cat->stand();
      QGraphicsScene::keyPressEvent(
          event);  // Передаем событие дальше для стандартной обработки
  }
}

void F_Scene::checkCollisions() {

  QList<QGraphicsItem*> itemsList = items();
  for (QGraphicsItem* item : itemsList) {
    // Проверяем, является ли элемент фруктом и сталкивается ли он с котом
    if (dynamic_cast<Fruits*>(item) && item->collidesWithItem(cat)) {
      removeItem(item);
      ++score;
      updateScoreText();
      delete item;
    }
    else{
        continue;
    }
  }
}

void F_Scene::gameOver() {
  inGame = false;
  checkCollisionsTimer->stop();
  cat->stand();
  foodCatScoreValue = score;
  emit foodCatcherGameOverSignal();
}

void F_Scene::updateTimerText() {
  if (timerText) {
    // Обновляем текст таймера
    QString htmlString = "<p> Left: " + QString::number(gameTime) + "</p>";
    timerText->setHtml(htmlString);
  }
}

void F_Scene::updateScoreText() {
  // Отображаем счет
  bestScore = score > bestScore ? score : bestScore;
  QString htmlString = "<p> Score: " + QString::number(score) + "</p>" +
                       "<p> Best score: " + QString::number(bestScore) + "</p>";
  scoreTextItem->setHtml(htmlString);
}

bool F_Scene::getInGame() const {
  return inGame;
}

void F_Scene::setInGame(bool value) {
  inGame = value;
}

void F_Scene::setUpFruitTimer() {
  fruitGeneratorTimer = new QTimer(this);
  connect(fruitGeneratorTimer, &QTimer::timeout, [=]() {
    Fruits* fr = new Fruits();
    addItem(fr);
  });
}

void F_Scene::setUpCollisionsTimer() {
  checkCollisionsTimer = new QTimer(this);
  connect(checkCollisionsTimer, &QTimer::timeout, [=]() {
    checkCollisions();
  });
}

void F_Scene::startGame() {

  inGame = true;
  score = 0;
  gameTime = GAME_TIME;

  if (!fruitGeneratorTimer->isActive()) {
    fruitGeneratorTimer->start(GENERATION_TIME);
  }
  if (!checkCollisionsTimer->isActive()) {
    checkCollisionsTimer->start(CHECK_TIME);
  }

  // Создаем таймер для обновления таймера игры
  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, [=]() {
    gameTime--;  // Уменьшаем время на 1 секунду
    updateTimerText();
    if (gameTime == 2) {
      fruitGeneratorTimer->stop();
    }
    if (gameTime <= 0) {
      timer->stop();
      delete timer;
      gameOver();
      return;
    }
  });
  timer->start(
      GENERATION_TIME);  // Запускаем таймер, чтобы он срабатывал каждую секунду
  updateTimerText();     // Обновляем текст таймера
}
