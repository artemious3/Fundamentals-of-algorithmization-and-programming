#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "vector.h"
#include "VectorIterator.h"
#include "pair.h"

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
    Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> myVector;

    myVector.push_back(Pair(Vector<int>{1, 2, 3}, Vector<Pair<int, double>>{{4, 5.0}, {4, 5.5}}));

    for (const auto& pair : myVector) {
        ui->textEdit->append("First vector:");
        for (const auto& elem : pair.first) {
            ui->textEdit->append(" " + QString::number(elem));
        }

        ui->textEdit->append("Second vector of pairs:");
        for (const auto& nested_pair : pair.second) {
            ui->textEdit->append("     (" + QString::number(nested_pair.first) + ", " + QString::number(nested_pair.second) + ")");
        }
    }
}



