#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>

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

void MainWindow::on_splitButton_clicked()
{
    // разбиение очереди на две: с положительными числами и с отрицательными числами
    while (!sourceQueue.isEmpty()) {
        int value = sourceQueue.dequeue();
        if (value < 0) {
            negativeQueue.enqueue(value);
        } else {
            positiveQueue.enqueue(value);
        }
    }

    negativeQueue.display(ui->negativeListWidget);
    positiveQueue.display(ui->positiveListWidget);
}

void MainWindow::on_showButton_clicked()
{
    ui->showButton->hide();

    // инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // заполнение исходной очереди
    for (int i = 0; i < 10; ++i) {
        int value = rand() % 201 - 100; // случайное число от -100 до 100
        sourceQueue.enqueue(value);
    }

    sourceQueue.display(ui->sourceListWidget);
}

void MainWindow::on_enqueueButton_clicked()
{
    srand(static_cast<unsigned int>(time(0)));
    int newNum = rand() % 201 - 100;
    sourceQueue.enqueue(newNum);
    ui->updateLabel->clear();
    ui->updateLabel->setText("В конец очереди добавлен элемент: " + QString::number(newNum));
}

void MainWindow::on_dequeueButton_clicked()
{
    if (sourceQueue.isEmpty() == false) {
        int lastNum = sourceQueue.dequeue();
        ui->updateLabel->clear();
        ui->updateLabel->setText("Удалён первый элемент, значение которого равно: " + QString::number(lastNum));
    }
    else {
        ui->updateLabel->clear();
        ui->updateLabel->setText("Очередь пустая!");
    }
}

void MainWindow::on_isEmptyButton_clicked()
{
    if (sourceQueue.isEmpty() == false) {
        ui->updateLabel->clear();
        ui->updateLabel->setText("Очередь не является пустой!");
    }
    else {
        ui->updateLabel->clear();
        ui->updateLabel->setText("Очередь пустая!");
    }
}

void MainWindow::on_showUpdateButton_clicked()
{
    ui->sourceListWidget->clear();
    sourceQueue.display(ui->sourceListWidget);
}

