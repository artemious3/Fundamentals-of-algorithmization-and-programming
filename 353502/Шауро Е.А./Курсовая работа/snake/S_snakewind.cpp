#include "S_snakewind.h"
#include "ui_snakewind.h"

SnakeWind::SnakeWind(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SnakeWind) {
  ui->setupUi(this);
  sscene = new S_Scene;
  sscene->setSceneRect(0, 0, SCENE_RECT, SCENE_RECT);

  // Добавляем фоновое изображение
  QGraphicsPixmapItem* pixItem =
      new QGraphicsPixmapItem(QPixmap(":/Images/backgroundSnake.jpeg")
                                  .scaled(QSize(SCENE_RECT, SCENE_RECT)));
  sscene->addItem(pixItem);
  pixItem->setPos(QPointF(0, 0));

  // Устанавливаем сцену в виджет
  ui->graphicsView->setFixedSize(SCENE_RECT, SCENE_RECT);
  ui->graphicsView->setScene(sscene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  connect(sscene, &S_Scene::snakeGameOverSignal, this, &SnakeWind::takeSnakeEndSignal);
}

SnakeWind::~SnakeWind() {
  delete ui;
}

void SnakeWind::on_snakeStartButton_clicked()
{ if (sscene->getInGame()) {

        QMessageBox messageBox(QMessageBox::Warning, "WARNING",
                               "The game was already started!", QMessageBox::Ok);

        messageBox.exec();

      } else {
        sscene->startGame();
      }

}

void SnakeWind::takeSnakeEndSignal()
{
    emit newScoreFromSnake();
}

void SnakeWind::closeEvent(QCloseEvent* event) {
  event->accept();
  emit windowClosed();
}
