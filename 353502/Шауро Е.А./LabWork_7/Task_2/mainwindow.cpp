#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QString phrases[5] = {"phrase1", "phrase2", "phrase3", "phrase4", "phrase5"};

  for (int i = 0; i < 5; ++i) {
    arr.append({i, phrases[i]});
  }

  QStandardItemModel* model = new QStandardItemModel(5, 2);
  model->setHorizontalHeaderLabels({"ID", "Phrase"});

  for (int i = 0; i < 5; ++i) {
    QStandardItem* idItem = new QStandardItem(QString::number(arr[i].id));
    QStandardItem* phraseItem = new QStandardItem(arr[i].info);
    model->setItem(i, 0, idItem);
    model->setItem(i, 1, phraseItem);
  }
  ui->tableView->setModel(model);
}

MainWindow::~MainWindow() {
  delete ui;
}
