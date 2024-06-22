#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::InfoWindow), num(0) {
  ui->setupUi(this);
  setFixedSize(INFO_SIZE, INFO_SIZE);

  infoScene = new MainScene();
  infoScene->setSceneRect(-100, -100, 200, 500);
  QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(
      QPixmap(":/Images/infoBack.png").scaled(QSize(INFO_SIZE, INFO_SIZE)));
  infoScene->addItem(pixItem);
  pixItem->setPos(QPointF(0, 0) -
                  QPointF(pixItem->boundingRect().width() / 2,
                          pixItem->boundingRect().height() / 2));

  ui->graphicsView->setScene(infoScene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  cat = new Pet();
  infoScene->addItem(cat);

  ui->label->setText(
      "Hello dear player! Welcome to the Tamagotchi game!\n Let's quickly "
      "analyze the main characteristics\n of your cat!");

  mood.append(Cool);
  mood.append(Standart);
  mood.append(Angry);
  mood.append(GoAway);

  description.append(
      "This is the best state of your pet.\n It is in it if all its "
      "characteristics are\n at least 90% complete.");
  description.append(
      "This is the normal state of your pet\n It is in it if all its "
      "characteristics are\n at least 40% complete.");
  description.append(
      "Be careful! Your pet is angry because\n you don't pay enough attention "
      "to "
      "him!\n If nothing is corrected soon, your pet may leave you!");
  description.append(
      "End of the game. The pet decided that it would\n be better for him with "
      "another owner and left\n you because one of his indicators dropped\n to "
      "zero");
}

InfoWindow::~InfoWindow() {
  delete infoScene;
  infoScene = nullptr;

  delete ui;
}

void InfoWindow::on_pushButton_clicked() {
  if (num >= 4) {
    num %= 4;
  }

  cat->setMood(mood[num]);
  cat->updateCatIcon();

  ui->label->setText(description[num]);
  ++num;
}
