#include "M3_scene.h"

M3_Scene::M3_Scene(QObject* parent)
    : QGraphicsScene(parent),
      score(0),
      startPos(QPointF(START_POS_X, START_POS_Y)),
      m_selectedGem(nullptr) {}

void M3_Scene::addGems() {

  arrOfGems = new GemsItem**[ROW_COUNT];
  for (int i = 0; i < ROW_COUNT; ++i) {
    arrOfGems[i] = new GemsItem*[COL_COUNT];
  }

  for (int row = 0; row < ROW_COUNT; ++row) {
    for (int col = 0; col < COL_COUNT; ++col) {
      // Вычисление позиции текущего гема
      QPointF gemPosition = startPos + QPointF(col * (GEM_SIZE + SPACING),
                                                    row * (GEM_SIZE + SPACING));
      GemsItem* gem = new GemsItem();
      gem->setPos(gemPosition);
      addItem(gem);
      arrOfGems[row][col] = gem;
      gem->setpRow(row);
      gem->setpCol(col);
    }
  }
  checkHorMatches();
  checkVertMatches();
  dropGems();

  score = 0;
  scoreText->setPlainText("Score:" + QString::number(score));
}

void M3_Scene::setIsBackground(bool value) {
  isBackground = value;
}

void M3_Scene::addScore() {
  QString htmlString = "<p> Score: " + QString::number(score) + "</p>";

  scoreText = new QGraphicsTextItem();
  QFont mFont("Consolas", TEXT_SIZE, QFont::Bold);
  scoreText->setHtml(htmlString);
  scoreText->setFont(mFont);
  scoreText->setDefaultTextColor(Qt::blue);
  addItem(scoreText);
  scoreText->setPos(QPointF(TEXT_X, TEXT_Y));
}

bool M3_Scene::getIsBackground() const
{
    return isBackground;
}

int M3_Scene::getScore() const
{
    return score;
}

void M3_Scene::dropGems() {
    for (int row = ROW_COUNT - 1; row >= 0; --row) {
    for (int col = COL_COUNT - 1; col >= 0; --col) {
      GemsItem* curGem = arrOfGems[row][col];

      if (curGem->getType() != -1) {
        continue;
      } else {
        // Если пустое место обнаружено в первом ряду, генерируем туда новый гем
        if (row == 0) {
          curGem = new GemsItem();
          QPointF pos = startPos + QPointF(col * (GEM_SIZE + SPACING),
                                                row * (GEM_SIZE + SPACING));
          curGem->setPos(pos);
          addItem(curGem);
          curGem->setpCol(col);
          curGem->setpRow(row);
          arrOfGems[row][col] = curGem;

        } else {
          GemsItem* upGem = arrOfGems[row - 1][col];
          int dur = 1;

          while (upGem->getType() == -1 && row - 1 - dur >= 0) {
            upGem = arrOfGems[row - 1 - dur][col];
            ++dur;
          }

          if (upGem->getType() == -1) {
            curGem = new GemsItem();
            QPointF pos = startPos + QPointF(col * (GEM_SIZE + SPACING),
                                                  row * (GEM_SIZE + SPACING));
            curGem->setPos(pos);
            addItem(curGem);
            curGem->setpCol(col);
            curGem->setpRow(row);
            arrOfGems[row][col] = curGem;
          }

          else {
            upGem = arrOfGems[row - dur][col];
            QPointF pos1 = curGem->scenePos();
            QPointF pos2 = upGem->scenePos();

            curGem->setPos(pos2);
            upGem->setPos(pos1);

            std::swap(arrOfGems[row][col], arrOfGems[row - dur][col]);

            int tempRow = curGem->getpRow();
            int tempCol = curGem->getpCol();
            curGem->setpRow(upGem->getpRow());
            curGem->setpCol(upGem->getpCol());
            upGem->setpRow(tempRow);
            upGem->setpCol(tempCol);
          }
        }
      }
    }
  }
  checkHorMatches();
  checkVertMatches();
}

void M3_Scene::deleteMatches(GemsItem* gem) {
  if (items().contains(gem)) {
    int row = gem->getpRow();
    int col = gem->getpCol();

    // Удаляем гем из сцены
    gem->setType(-1);
    removeItem(gem);
    arrOfGems[row][col]->setType(-1);

  } else {
    return;
  }
}

void M3_Scene::swapGems(GemsItem* gem1, GemsItem* gem2) {
  if (!gem1 || !gem2) {
    return;
  }

  QPointF pos1 = gem1->scenePos();
  QPointF pos2 = gem2->scenePos();

  bool areAdjacent = (((qAbs(pos1.x() - pos2.x()) < GEM_SIZE * 2 + SPACING) &&
                       (qAbs(pos1.y() - pos2.y()) < GEM_SIZE * 2 + SPACING)) ||

                      ((qAbs(pos1.y() - pos2.y()) < GEM_SIZE + SPACING) &&
                       (qAbs(pos1.x() - pos2.x()) < GEM_SIZE + SPACING)));

  if (!areAdjacent) {
    return;
  } else {
    // Поменять местами гемы на сцене
    gem1->setPos(pos2);
    gem2->setPos(pos1);

    // Проверяем, чтобы индексы не выходили за границы массива
    int row1 = gem1->getpRow();
    int col1 = gem1->getpCol();
    int row2 = gem2->getpRow();
    int col2 = gem2->getpCol();

    if (row1 >= 0 && row1 < ROW_COUNT && col1 >= 0 && col1 < COL_COUNT &&
        row2 >= 0 && row2 < ROW_COUNT && col2 >= 0 && col2 < COL_COUNT) {

      std::swap(arrOfGems[row1][col1], arrOfGems[row2][col2]);

    } else {
      qDebug() << "Index out of bounds!";
    }

    // Обновить указатели pRow и pCol у гемов
    int tempRow = gem1->getpRow();
    int tempCol = gem1->getpCol();
    gem1->setpRow(gem2->getpRow());
    gem1->setpCol(gem2->getpCol());
    gem2->setpRow(tempRow);
    gem2->setpCol(tempCol);

    checkHorMatches();
    checkVertMatches();
    dropGems();
  }
}

void M3_Scene::checkHorMatches() {
  for (int row = 0; row < ROW_COUNT; ++row) {
    int count = 1;
    for (int col = 0; col < COL_COUNT - 1; ++col) {

      GemsItem* currentGem = arrOfGems[row][col];
      GemsItem* nextGem = arrOfGems[row][col + 1];

      if (currentGem->getType() != -1 &&
          nextGem->getType() == currentGem->getType()) {
        ++count;
      } else {
        if (count >= 3) {
          ++score;
          for (int i = 0; i < count; ++i) {
            deleteMatches(arrOfGems[row][col - i]);
          }
          dropGems();
        }
        count = 1;
      }
    }
    if (count >= 3) {
      ++score;
      for (int i = 0; i < count; ++i) {
        deleteMatches(arrOfGems[row][LAST_COL - i]);
      }
      dropGems();
    }
  }
}

void M3_Scene::checkVertMatches() {
  for (int col = 0; col < COL_COUNT; ++col) {
    int count = 1;
    for (int row = 0; row < ROW_COUNT - 1; ++row) {

      GemsItem* currentGem = arrOfGems[row][col];
      GemsItem* nextGem = arrOfGems[row + 1][col];

      if (currentGem->getType() != -1 &&
          nextGem->getType() == currentGem->getType()) {
        ++count;
      } else {
        if (count >= 3) {
          ++score;
          for (int i = 0; i < count; ++i) {
            deleteMatches(arrOfGems[row - i][col]);
          }
          dropGems();
        }
        count = 1;
      }
    }
    if (count >= 3) {
      ++score;
      for (int i = 0; i < count; ++i) {
        deleteMatches(arrOfGems[LAST_ROW - i][col]);
      }
      dropGems();
    }
  }
}

void M3_Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  gem = nullptr;
  QPointF clickPos = event->scenePos();
  QGraphicsItem* item = itemAt(clickPos, QTransform());
  gem = qgraphicsitem_cast<GemsItem*>(item);

  if (gem && !gem->getIsBackground()) {
    if (!m_selectedGem) {
      m_selectedGem = gem;
    } else {
      checkHorMatches();
      checkVertMatches();
      swapGems(m_selectedGem, gem);
      scoreText->setPlainText("Score:" + QString::number(score));
      m_selectedGem = nullptr;
    }
  }
}
