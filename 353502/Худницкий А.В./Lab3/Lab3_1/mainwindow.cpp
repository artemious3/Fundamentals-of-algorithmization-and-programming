#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

QString decimalToBinary(int decimal) {
    if (decimal == 0) {
        return "";
    }
    return decimalToBinary(decimal / 2) + QString::number(decimal % 2);
}

void MainWindow::on_pushButton_clicked()
{
    QString decimalString = ui->lineEdit_2->text();
    int decimalNumber = decimalString.toInt();
    QString binaryNumber = decimalToBinary(decimalNumber);
    if (binaryNumber == "") {
        binaryNumber = "0";
    }
    ui->lineEdit->setText(binaryNumber);
}
