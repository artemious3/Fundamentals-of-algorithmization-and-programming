#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  myHashTable = new HashTable();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_addButton_clicked() {
  myHashTable->insert(QRandomGenerator::global()->bounded(500));
  updateTable();
}

void MainWindow::updateTable() {
  QStandardItemModel* model = new QStandardItemModel(ui->tableView);

  model->setRowCount(myHashTable->getSize());
  model->setColumnCount(2);

  for (int i = 0; i < myHashTable->getSize(); ++i) {
    QString id = QString::number(i);
    QString rowData;
    QStack<int> temp = myHashTable->table[i];
    while (!temp.empty()) {
      rowData += QString::number(temp.top()) + " ";
      temp.pop();
    }

    QStandardItem* idItem = new QStandardItem(id);
    model->setItem(i, 0, idItem);

    QStandardItem* dataItem = new QStandardItem(rowData);
    model->setItem(i, 1, dataItem);
  }

  ui->tableView->setModel(model);
}

void MainWindow::on_deleteButton_clicked() {
  int key = ui->textEdit->toPlainText().toInt();
  int success = myHashTable->removeByKey(key);

  QMessageBox::information(
      this, "Info",
      QString(success == -1 ? "Не найдено элемента с таким ключом"
                            : "Элемент удален"));
  updateTable();
}

void MainWindow::on_seeButton_clicked() {
  auto arr = myHashTable->getAllKeys();
  QString text = "";
  for (auto a : arr) {
    text += QString::number(a) + ' ';
  }
  QMessageBox::information(this, "Info", "Ключи:\n" + text);
}

void MainWindow::on_doButton_clicked() {
    if(myHashTable->getCounter() == 0){
        return;
    }
  QMessageBox::information(
      this, "Info",
      "Количество элементов, с ключами больше среднего:\n" +
          QString::number(myHashTable->countLargestKeys()));
}
