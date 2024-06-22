#include "B_birdwind.h"
#include "ui_birdwind.h"

BirdWind::BirdWind(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::BirdWind), intervalScore(0) {
  ui->setupUi(this);
  setFixedSize(LENGTH, WIDTH);

  bscene = new B_Scene;
  bscene->setSceneRect(SCENE_RECT_X, SCENE_RECT_Y, SCENE_RECT_LEN,
                       SCENE_RECT_WID);

  QGraphicsPixmapItem* pixItem =
      new QGraphicsPixmapItem(QPixmap(":/Images/backgroundBird.png"));
  bscene->addItem(pixItem);
  pixItem->setPos(QPointF(0, 0) -
                  QPointF(pixItem->boundingRect().width() / 2,
                          pixItem->boundingRect().height() / 2));

  ui->graphicsView->setScene(bscene);
  bscene->addBird();
  connect(bscene, &B_Scene::birdGameOverSignal, this,
          &BirdWind::takeBirdEndSignal);
}

BirdWind::~BirdWind() {
  delete ui;
}

void BirdWind::on_startBirdButton_clicked() {

  bscene->startGame();
}

void BirdWind::takeBirdEndSignal() {
  emit newScoreFromBird();
}

void BirdWind::closeEvent(QCloseEvent* event) {
  event->accept();
  emit windowClosed();
}
