#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (int i = 0; i < 10; ++i) {
    queue.enqueue(QRandomGenerator::global()->bounded(100));
  }

  queue.cur = queue.first;
  updateTextBrowser();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_ringButton_clicked() {

  QMessageBox::information(this, "INFO",
                           "Двусвязный список преобразован в кольцо");
  queue.convertToCircular();
}

void MainWindow::updateTextBrowser() {

  int i = queue.getSize();
  Node* element = queue.first;
  QString text = "";
  while (i--) {
    text += QString::number(element->data) + " ";
    element = element->next;
  }
  ui->textBrowser->setText(text);
  ui->elementlabel->setText(QString::number(queue.cur->data));
}

void MainWindow::on_deleteButton_clicked() {
  if (queue.cur == queue.first) {
    queue.cur = queue.cur->next;
  }
  queue.dequeue();
  updateTextBrowser();
}

void MainWindow::on_addButton_clicked() {
  queue.enqueue(QRandomGenerator::global()->bounded(100));
  updateTextBrowser();
}

void MainWindow::on_prevButton_clicked() {

  queue.goPrev();
  updateTextBrowser();
}

void MainWindow::on_nextButton_clicked() {
  queue.goNext();
  updateTextBrowser();
}
