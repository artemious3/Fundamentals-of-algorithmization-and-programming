#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sorts.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QElapsedTimer>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    sorts = new Sorts();

    label = new QLabel(this);
    ui->statusbar->addWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sorts;
}

void MainWindow::on_Vector_clicked() {
    qDebug() << "Vector";
    int arraySize = ui->lineEdit->text().toInt();
    QGraphicsScene *scene = ui->graphicsView->scene();
    sorts->setSize(arraySize, scene);
}

void MainWindow::on_MergeSort_clicked() {
    qDebug() << "MergeSort";
    timer.start();
    sorts->mergeSort(ui->graphicsView->scene());
    qint64 elapsed_ms = timer.elapsed();
    label->setText("MergeSort: " + QString::number(elapsed_ms) + " ms");
    ui->centralwidget->setFocus();
}

void MainWindow::on_HeapSort_clicked() {
    qDebug() << "HeapSort";
    timer.start();
    sorts->heapSort(ui->graphicsView->scene());
    qint64 elapsed_ms = timer.elapsed();
    label->setText("HeapSort: " + QString::number(elapsed_ms) + " ms");
    ui->centralwidget->setFocus();
}

void MainWindow::on_QuickSort_clicked(){
    qDebug() << "QuickSort";
    timer.start();
    sorts->quickSort(ui->graphicsView->scene());
    qint64 elapsed_ms = timer.elapsed();
    label->setText("QuickSort: " + QString::number(elapsed_ms) + " ms");
    ui->centralwidget->setFocus();
}


void MainWindow::on_InterpolationSort_clicked() {
    qDebug() << "InterpolationSort";
    timer.start();
    sorts->interpolationSort(ui->graphicsView->scene());
    qint64 elapsed_ms = timer.elapsed();
    label->setText("InterpolationSort: " + QString::number(elapsed_ms) + " ms");
    ui->centralwidget->setFocus();
}

void MainWindow::on_NumberButton_clicked() {
    int number = ui->number->text().toInt();
    int index = sorts->binsearch(sorts->getArray(), number);
    ui->BinSearchEdit->setText(QString::number(index));

    if (index != -1) {
        int binPowResult = sorts->binpow(index, sorts->getSize(), ui->number->text().toInt());
        ui->BinPowEdit->setText(QString::number(binPowResult));
    } else {
        ui->BinPowEdit->setText("-1");
    }
}
