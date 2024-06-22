#include "M3_match3wind.h"
#include "ui_match3wind.h"

Match3Wind::Match3Wind(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Match3Wind) {
  ui->setupUi(this);
  setFixedSize(LEN, WID);

  mscene = new M3_Scene;
  mscene->setIsBackground(true);
  mscene->setSceneRect(-250, -300, 500, 600);

  QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(
      QPixmap(":/Images/backgroundMatch3.png")
          .scaled(QSize(LEN, WID), Qt::KeepAspectRatio));
  mscene->addItem(pixItem);
  pixItem->setPos(QPointF(0, 0) -
                  QPointF(pixItem->boundingRect().width() / 2,
                          pixItem->boundingRect().height() / 2));

  ui->graphicsView->setScene(mscene);
  mscene->addScore();
  mscene->addGems();
}

Match3Wind::~Match3Wind() {
  delete ui;
}

void Match3Wind::closeEvent(QCloseEvent* event) {
  match3ScoreValue = mscene->getScore();
  event->accept();
  emit windowClosed();
}
