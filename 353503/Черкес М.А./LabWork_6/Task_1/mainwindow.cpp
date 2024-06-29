#include "mainwindow.h"
#include <QMessageBox>
#include "Matheric.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->button1, &QPushButton::clicked, this, &MainWindow::slot1);
  connect(ui->button2, &QPushButton::clicked, this, &MainWindow::slot2);
  connect(ui->button3, &QPushButton::clicked, this, &MainWindow::slot3);
  connect(ui->button4, &QPushButton::clicked, this, &MainWindow::slot4);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::slot2() {
  ui->textEdit->clear();
  QString textAmount = ui->lineEditAmount->text();
  QString textPrice = ui->lineEditPrice->text();
  QString textGender = ui->lineEditGender->text();
  QString textInStock = ui->lineEditInStock->text();
  if (textAmount.isEmpty() || textPrice.isEmpty() || textGender.isEmpty() ||
      textInStock.isEmpty()) {
    QMessageBox::critical(this, "Ошибка", "Некорректное значение!");
    return;
  }
  Matheric Matheric3;
  bool ok = false;
  Matheric3.peoples = textAmount.toInt(&ok);
  Matheric3.perimeter = textPrice.toDouble(&ok);
  if (!textGender.isEmpty()) {
    Matheric3.size = textGender.at(0).toLatin1();
  } else {
    QMessageBox::critical(this, "Ошибка", "Некорректное значение!");
    return;
  }
  if (textInStock.toLower() == "yes" || textInStock == "1") {
    Matheric3.isSeasOpen = true;
  } else if (textInStock.toLower() == "no" || textInStock == "0") {
    Matheric3.isSeasOpen = false;
  } else {
    QMessageBox::critical(this, "Ошибка", "Некорректное значение!");
    return;
  }
  if (Matheric3.size != 'b' && Matheric3.size != 's') {
    QMessageBox::critical(this, "Ошибка", "Некорректное значение!");
    return;
  }
  if (ok) {
    QString output = printMatheric(Matheric3);
    ui->textEdit->setText(output);

  } else {
    QMessageBox::critical(this, "Ошибка", "Некорректное значение!");
    return;
  }
}

QString MainWindow::printMatheric(Matheric& Matheric) {
  QString result = QString("%1 | %2 | %3 | %4 | %5 | %6")
                       .arg(QString::number(Matheric.peoples))
                       .arg(QString::number(Matheric.perimeter, 'b', 2))
                       .arg(Matheric.size)
                       .arg(Matheric.isSeasOpen ? "большой" : "маленький")
                       .arg(Matheric::getNationsString())
                       .arg(Matheric::getTemperaturesString());

  return result;
}

void MainWindow::slot3() {
  Matheric matheric;
  Matheric* pmatheric = &matheric;
  pmatheric->peoples = 1447760;
  pmatheric->perimeter = 435669.99;
  pmatheric->size = 'b';
  pmatheric->isSeasOpen = false;
  QString result = QString("%1 | %2 | %3 | %4 | %5 | %6")
                       .arg(pmatheric->peoples)
                       .arg(pmatheric->perimeter)
                       .arg(pmatheric->size)
                       .arg(pmatheric->isSeasOpen ? "большой" : "маленький")
                       .arg(Matheric::getNationsString())
                       .arg(Matheric::getTemperaturesString());

  ui->textEdit->setText(result);
}

void MainWindow::slot4() {
  Matheric matheric;
  Matheric& mathericRef = matheric;

  mathericRef.peoples = 1111104660;
  mathericRef.perimeter = 9934359.99;
  mathericRef.size = 's';
  mathericRef.isSeasOpen = true;

  QString result = QString("%1 | %2 | %3 | %4 | %5 | %6")
                       .arg(mathericRef.peoples)
                       .arg(mathericRef.perimeter)
                       .arg(mathericRef.size)
                       .arg(mathericRef.isSeasOpen ? "большой" : "маленький")
                       .arg(Matheric::getNationsString())
                       .arg(Matheric::getTemperaturesString());
  ui->textEdit->setText(result);
}

void MainWindow::slot1() {
  ui->textEdit->clear();
  int peoples = 2 * 2 + 1;
  double perimeter = 0.75 * 10 * 10 * 2;
  Matheric matheric1 = {peoples, perimeter, 'b', true};
  Matheric matheric2;
  matheric2.peoples = 300;
  matheric2.perimeter = 2000000.0;
  matheric2.size = 's';
  matheric2.isSeasOpen = false;
  QString output1 = printMatheric(matheric1);
  QString output2 = printMatheric(matheric2);

  ui->textEdit->setText(output1 + "\n" + output2);
}
