#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <QLineEdit>
#include <QStringList>
#include <vector>

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

int findMedian(const std::vector<int>& vec) {
    std::vector<int> sortedVec = vec;
    std::sort(sortedVec.begin(), sortedVec.end());

    int sizeOfvec = sortedVec.size();
    if (sizeOfvec % 2 == 0) return (sortedVec[sizeOfvec / 2 - 1] + sortedVec[sizeOfvec / 2]) / 2;
    else return sortedVec[sizeOfvec / 2];
}

std::vector<int> mediansOfVector(const std::vector<int>& vector1) {
    std::vector<int> vector2;
    int sizeOfVector1 = vector1.size();

    for (int i = 0; i < sizeOfVector1; i += 3) {
        std::vector<int> tripletOfNumbers;
        for (int j = i; j < std::min(i + 3, sizeOfVector1); ++j) {
            tripletOfNumbers.push_back(vector1[j]);
        }
        vector2.push_back(findMedian(tripletOfNumbers));
    }

    return vector2;
}

void MainWindow::on_pushButton_clicked()
{

    ui->textEdit->clear();
    std::vector<int> vector1;
    QString textForVector = ui->lineEdit->text();
    QStringList stringNumberList = textForVector.split(" ");

    for (const QString& stringNumber : stringNumberList) {
        bool flag;
        int number = stringNumber.toInt(&flag);
        if (flag) {
            vector1.push_back(number);
        }
    }

    std::vector<int> vector2 = mediansOfVector(vector1);

    for (int median : vector2) {
        QString medianString = QString::number(median);
        ui->textEdit->insertPlainText(QString::number(median) + " ");
    }
}

