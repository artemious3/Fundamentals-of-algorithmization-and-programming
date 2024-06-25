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


void MainWindow::on_pushButton_2_clicked()
{
    figure->setWindowFlags(Qt::Popup);
    figure->resize(300, 300);
    figure->move(400, 400);
    figure->show();
}

void MainWindow::on_pushButton_clicked()
{
    wave->setWindowFlags(Qt::Popup);
    wave->resize(300, 300);
    wave->move(400, 400);
    wave->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    close();
}
