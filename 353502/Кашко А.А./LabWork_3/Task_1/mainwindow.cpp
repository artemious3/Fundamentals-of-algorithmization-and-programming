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
    //получаю введённое пользователем число и проверяю число ли это
    bool test;
    double num = ui->textEdit->toPlainText().toDouble(&test);

    if (test) {
        QString binary = doubleToBinary(num);
        ui->textBrowser->setText(binary);
    } else {
        ui->textBrowser->setText("Ошибка! Повторите ввод!");
    }
}

QString MainWindow::doubleToBinary(double num)
{
    // Получаем целую и дробную части числа
    bool sign = false;
    if (num < 0) {
        num = num * (-1);
        sign = true;
    }
    int integerPart = static_cast<int>(num);
    double fractionalPart = num - integerPart;

    QString binaryInteger;
    QString binaryFractional;

    // Преобразование целой части в двоичную систему
    if (integerPart > 0) {
        binaryInteger = doubleToBinaryHelper(integerPart);
    } else {
        binaryInteger = "0";
    }

    // Преобразование дробной части в двоичную систему
    while (fractionalPart > 0) {
        fractionalPart *= 2;
        int bit = static_cast<int>(fractionalPart);
        binaryFractional += QString::number(bit);
        if (bit == 1) {
            fractionalPart -= bit;
        }
        if (binaryFractional.length() > 10) {
            break; // ограничение на количество разрядов
        }
    }

    if (sign) {
        return '1' + binaryInteger + (binaryFractional.isEmpty() ? "" : "." + binaryFractional);
    }

    else {
        return binaryInteger + (binaryFractional.isEmpty() ? "" : "." + binaryFractional);
    }
}

QString MainWindow::doubleToBinaryHelper(int num)
{
    if (num == 0) {
        return "";
    } else {
        return doubleToBinaryHelper(num / 2) + QString::number(num % 2);
    }
}
