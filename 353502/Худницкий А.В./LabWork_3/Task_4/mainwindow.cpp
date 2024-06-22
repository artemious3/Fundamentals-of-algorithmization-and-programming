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

void hanoi(int n, char from_rod, char to_rod, char aux_rod, Ui::MainWindow *ui) {
    if (n == 1) {
        ui->textEdit->append("Переместить кольцо 1 с кола " + QString(from_rod) + " на кол " + QString(to_rod) + "\n");
        return;
    } else {
    hanoi(n - 1, from_rod, aux_rod, to_rod, ui);
    ui->textEdit->append("Переместить кольцо " + QString::number(n) + " с кола " + QString(from_rod) + " на кол " + QString(to_rod)+ "\n") ;
    hanoi(n - 1, aux_rod, to_rod, from_rod, ui);
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    QString numberString = ui->lineEdit->text();
    int numberInt = numberString.toInt();
    hanoi(numberInt, 'A', 'C', 'B', ui);
}
