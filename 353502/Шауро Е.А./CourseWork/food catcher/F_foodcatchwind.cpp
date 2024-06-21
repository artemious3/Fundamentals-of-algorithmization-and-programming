#include "F_foodcatchwind.h"
#include "ui_foodcatchwind.h"

FoodCatchWind::FoodCatchWind(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::FoodCatchWind) {
  ui->setupUi(this);
  setFixedSize(SIDE, SIDE);

  fscene = new F_Scene;
  fscene->setSceneRect(0, 0, SC_RECT, SC_RECT);

  QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(
      QPixmap(":/Images/backgroundForCatch.png")
          .scaled(QSize(SIDE, SIDE), Qt::KeepAspectRatio));
  fscene->addItem(pixItem);

  ui->graphicsView->setScene(fscene);
  fscene->addPlayerAndTextItems();

  // Убираем полосы прокрутки
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Устанавливаем выравнивание для фонового изображения
  ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  connect(fscene, &F_Scene::foodCatcherGameOverSignal, this, &FoodCatchWind::takeFoodCatEndSignal);
}

FoodCatchWind::~FoodCatchWind() {
  delete ui;
}

void FoodCatchWind::on_startFoodCatGameButton_clicked() {
  if (fscene->getInGame()) {

    QMessageBox messageBox(QMessageBox::Warning, "WARNING",
                           "The game was already started!", QMessageBox::Ok);

    messageBox.exec();

  } else {
    fscene->startGame();
  }
}

void FoodCatchWind::takeFoodCatEndSignal()
{
    emit newScoreFromFoodCat();
}

void FoodCatchWind::closeEvent(QCloseEvent* event) {
  event->accept();
  emit windowClosed();
}
