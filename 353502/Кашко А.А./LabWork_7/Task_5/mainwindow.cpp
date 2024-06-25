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
    delete ui;
}

void MainWindow::on_pushbackButton_clicked()
{
    deq.push_back(ui->spinBox->value());
    printDeq();
}


void MainWindow::on_popbackButton_2_clicked()
{
    deq.pop_back();
    printDeq();
}


void MainWindow::on_pushfrontButton_clicked()
{
    deq.push_front(ui->spinBox->value());
    printDeq();
}


void MainWindow::on_popfrontButton_clicked()
{
    deq.pop_front();
    printDeq();
}


void MainWindow::on_clearButton_clicked()
{
    deq.clear();
    printDeq();
}

void MainWindow::printDeq()
{
    ui->textEdit->clear();
    for (auto el : deq) {
        ui->textEdit->setText(ui->textEdit->toPlainText() + " \n" + QString::number(el));
    }
}

void MainWindow::on_initButton_clicked()
{
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    deq.push_back(4);
    deq.push_back(5);

    QString text;
    for (int i = 0; i < deq.size(); ++i)
    {
        text.append(QString::number(deq[i]) + "\n");
    }

    ui->textEdit->setPlainText(text);
}

