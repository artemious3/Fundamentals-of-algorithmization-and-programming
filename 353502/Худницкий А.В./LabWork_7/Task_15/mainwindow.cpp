#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <sstream>
#include "Deque.h"

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
    ui->textEdit->clear();
    std::istringstream iss(ui->lineEdit->text().toStdString());
    int number;

    while (iss >> number) {
        myDeque.push_back(number);
    }

    Node* current = myDeque.head;
    QString text;
    while (current != nullptr) {
        text += QString::number(current->value) + " ";
        current = current->next;
    }
    ui->textEdit->setText(text.trimmed());
}


void MainWindow::on_pushButton_8_clicked()
{
    myDeque.clear();

    Node* current = myDeque.head;
    QString text;
    while (current != nullptr) {
        text += QString::number(current->value) + " ";
        current = current->next;
    }
    ui->textEdit->setText(text.trimmed());
}

void MainWindow::on_pushButton_7_clicked()
{
    if (myDeque.isEmpty()) {
        ui->lineEdit_5->setText("True");
    }
    else ui->lineEdit_5->setText("False");
}


void MainWindow::on_pushButton_6_clicked()
{
    QString stringValue = QString::number(myDeque.getSize());
    ui->lineEdit_4->setText(stringValue);
}


void MainWindow::on_pushButton_9_clicked()
{
    myDeque.swapMaxMin();
    Node* current = myDeque.head;
    QString text;
    while (current != nullptr) {
        text += QString::number(current->value) + " ";
        current = current->next;
    }
    ui->textEdit->setText(text.trimmed());
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QString str = ui->lineEdit_2->text();
    int value = str.toInt();


    myDeque.push_back(value);

    Node* current = myDeque.head;
    QString text;
    while (current != nullptr) {
        text += QString::number(current->value) + " ";
        current = current->next;
    }
    ui->textEdit->setText(text.trimmed());
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    QString str = ui->lineEdit_2->text();
    int value = str.toInt();


    myDeque.push_front(value);

    Node* current = myDeque.head;
    QString text;
    while (current != nullptr) {
        text += QString::number(current->value) + " ";
        current = current->next;
    }
    ui->textEdit->setText(text.trimmed());
}


void MainWindow::on_pushButton_4_clicked()
{
    QString stringValue = QString::number(myDeque.peekBack());
    ui->lineEdit_3->setText(stringValue);
}


void MainWindow::on_pushButton_5_clicked()
{
    QString stringValue = QString::number(myDeque.peekFront());
    ui->lineEdit_3->setText(stringValue);
}

