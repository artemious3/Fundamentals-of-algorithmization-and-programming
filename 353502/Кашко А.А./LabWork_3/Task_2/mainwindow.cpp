#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool check1, check2;
    int resultFunction = 0;
    int num1 = ui->textEdit->toPlainText().toInt(&check1);
    int num2 = ui->textEdit_2->toPlainText().toInt(&check2);

    ui->textEdit->clear();
    ui->textEdit_2->clear();

    if (check1 && check2 && num1 >= 0 && num2 >= 0) {
        resultFunction = ackermann(num1, num2);
        QString result = QString::number(resultFunction);
        ui->textBrowser->setText(result);
    }
}

int MainWindow::ackermann(int num1, int num2)
{
    if (num1 == 0) {
        return num2 + 1;
    } else if (num1 > 0 && num2 == 0) {
        return ackermann(num1 - 1, 1);
    } else {
        return ackermann(num1 - 1, ackermann(num1, num2 - 1));
    }
}
