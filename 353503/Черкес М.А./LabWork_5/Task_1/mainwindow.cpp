#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include <QVector>
#include <QtGui>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timer(new QTimer(this)) {
  ui->setupUi(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

  if (event->key() == Qt::Key_0) {

    QString str = QFileDialog::getOpenFileName(nullptr, "Choose file", "",
                                               "Текстовые файлы (*.txt)");
    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {
      fileContent = QString::fromUtf8(file.readAll());
      ui->text_Language->setText(fileContent);
      file.close();
    } else {
      qDebug() << "Ошибка при открытии файла: " << file.errorString();
    }
  }

  if (event->key() == Qt::Key_Escape) {

    if (timer->isActive()) {
      stopTimer();
    } else {
      startTimer();
    }

    enteredText.remove(enteredText.length() - 1, 1);
  }

  if (event->key() == Qt::Key_Backspace) {
    enteredText.remove(enteredText.length() - 1, 1);  //
  } else {
    enteredText += event->text();  // Добавляем введенный текст к тексту
  }
  QTimer timer;
  timer.setInterval(1000);

  ui->label->setText(enteredText);
  if (enteredText.length() == fileContent.length()) {
    stopTimer();
    ComparisonText(enteredText, fileContent);

  } else if (enteredText.length() > fileContent.length()) {
    messageFunction();
  }
}

void MainWindow::ComparisonText(QString text, QString input) {
  int len = text.size();
  for (int i = 0; i < len - 1; ++i) {
    if (text[i] != input[i]) {
      wrong++;
    }
  }

  double accuracy = (100 * (len - wrong)) / len;
  ui->correctly->setText(QString::number(accuracy) + " % ");
}

void MainWindow::messageFunction() {

  QMessageBox msgBox(this);
  msgBox.setWindowTitle("Предупреждение");
  msgBox.setText("Текст написан");
  msgBox.setIcon(QMessageBox::Information);
  msgBox.exec();
}

void MainWindow::startTimer() {
  timer->start(1000);  // Таймер с интервалом 1 секунда
  ui->Qtimer->setText("Timer started");
}

void MainWindow::stopTimer() {
  timer->stop();
  ui->Qtimer->setText("Timer stopped");
  ui->time->setText(QString::number(counter) + "seconds");
  counter = 0;
}

void MainWindow::updateTimer() {
  ++counter;
  ui->Qtimer->setText("Elapsed time: " + QString::number(counter) + " seconds");
}
