#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    connect(ui ->ButtonBalloon, SIGNAL(clicked()), SLOT(on_ButtonBalloon_clicked()));
    connect(ui ->ButtonEllipse, SIGNAL(clicked()), SLOT(on_ButtonEllipse_clicked()));
    delete ui;
}

void MainWindow::on_ButtonEllipse_clicked() {
    ellipse->show();
}

void MainWindow::on_ButtonBalloon_clicked() {
    balloon->show();
}

