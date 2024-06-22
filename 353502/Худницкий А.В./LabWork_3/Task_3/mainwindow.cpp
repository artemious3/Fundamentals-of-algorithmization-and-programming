#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int digitsCount(int n) {
    if (n == 0) {
        return 0;
    }
    return 1 + digitsCount(n / 10);
}

int reverseNumber(int n, int digits) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) * pow(10, digits - 1) + reverseNumber(n / 10, digits - 1);
}

void MainWindow::on_pushButton_clicked()
{
    QString numberString = ui->lineEdit->text();
    int numberInt = numberString.toInt();
    int digits = digitsCount(numberInt);
    int invertednumber = reverseNumber(numberInt, digits);
    QString invertednumberString = QString::number(invertednumber);
    ui->lineEdit_2->setText(invertednumberString);
}
