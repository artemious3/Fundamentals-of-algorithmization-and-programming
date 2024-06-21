#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushBackButton_clicked() {
  int i = QRandomGenerator::global()->bounded(100);

  deque.push_back(i);
  updateTextBrowser();
}

void MainWindow::updateTextBrowser() {
  QString text = "";

  auto it = deque.begin();

  while (it != deque.end()) {
    text.push_back(QString::number(*it));
    ++it;
  }

  ui->textBrowser->setText(text);
}

void MainWindow::on_pushFrontButton_clicked()
{
    int i = QRandomGenerator::global()->bounded(100);
    qDebug() << i;
    deque.push_front(i);
    updateTextBrowser();
}

void MainWindow::on_popBackButton_clicked()
{
    deque.pop_back();
    updateTextBrowser();
}

void MainWindow::on_popFrontButton_clicked()
{
    deque.pop_front();
    updateTextBrowser();
}

void MainWindow::on_emptyButton_clicked()
{
    QMessageBox::information(this, "INFO", QString(deque.isEmpty()? "Очередь пуста" : "Очередь не пуста"));
}

void MainWindow::on_clearButton_clicked()
{
    deque.clear();
    updateTextBrowser();
}

void MainWindow::on_sizeButton_clicked()
{
    QMessageBox::information(this, "INFO", QString("Размер очереди : %1").arg(deque.getSize()));
}
