#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    deq.push_back(10);
    deq.push_back(10);
    deq.push_back(10);
    deq.push_back(123);
    deq.push_back(2134);


    qDebug() << deq[0] << deq[1] << deq.size() << deq.empty();

    deq.clear();
    qDebug() << deq.size() << deq.empty();

    printDeque();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printDeque()
{
    ui->listWidget->clear();

    for(int i = 0; i < deq.size(); i++)
    {
        ui->listWidget->addItem(QString::number(deq[i]));
    }

    ui->lineEmpty->setText(deq.empty() ? "true" : "false");
    ui->lineSize->setText(QString::number(deq.size()));
}




void MainWindow::on_push_frontButton_clicked()
{
    deq.push_front(ui->spinBox->value());
    printDeque();
}
void MainWindow::on_push_backButton_clicked()
{
    deq.push_back(ui->spinBox->value());
    printDeque();
}




void MainWindow::on_pop_frontButton_clicked()
{
    deq.pop_front();
    printDeque();
}

void MainWindow::on_pop_backButton_clicked()
{
    deq.pop_back();
    printDeque();
}
void MainWindow::on_clearButton_clicked()
{
    deq.clear();
    printDeque();
}

