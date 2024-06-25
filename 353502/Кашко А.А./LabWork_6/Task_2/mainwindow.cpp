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

void MainWindow::on_menuButton_clicked()
{
    if(ui->radioButton->isChecked()) {
        WorkTextFile *screen = new WorkTextFile();
        screen->show();
    }
    if(ui->radioButton_3->isChecked()) {
        WorkMassFile *screen = new WorkMassFile();
        screen->show();
    }
    if(ui->radioButton_5->isChecked()) {
        WorkStructFile *screen = new WorkStructFile();
        screen->show();
    }
    if(ui->radioButton_7->isChecked()) {
        WorkStructBinFile *screen = new WorkStructBinFile();
        screen->show();
    }
    if(ui->radioButton_9->isChecked()) {
        WorkSentenceFile *screen = new WorkSentenceFile();
        screen->show();
    }
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

