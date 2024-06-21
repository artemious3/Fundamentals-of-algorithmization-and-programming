#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(450, 250);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::calculateMedian);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateMedian()
{
    QString input = ui->arrayInputTextEdit->toPlainText();
    QStringList numbers = input.split(" ");
    numbers.removeAll("");

    // Проверка корректности ввода данных
    bool validInput = true;
    QVector<int> a;
    foreach(QString number, numbers) {
        bool ok;
        int num = number.toInt(&ok);
        if (!ok) {
            validInput = false;
            break;
        }
        a.append(num);
    }

    if (!validInput) {
        ui->errorLabel->setText("НЕКОРРЕКТНЫЙ ВВОД!!!");
        return;
    }

    QVector<int> b;
    int i = 0;
    while (i < a.size()) {
        QVector<int> triplet;
        for (int j = 0; j < 3 && i < a.size(); ++j, ++i) {
            triplet.append(a[i]);
        }
        std::sort(triplet.begin(), triplet.end());
        if (triplet.size() % 2 == 0) {
            b.append((*triplet.begin() + *triplet.end()) / 2);
        } else {
            b.append(triplet[triplet.size() / 2]);
        }
    }

    QString result = " Mедианы: {";
    for (int i = 0; i < b.size(); ++i) {
        result += QString::number(b[i]);
        if (i != b.size() - 1) {
            result += ", ";
        }
    }
    result += "}";
    ui->outputLabel->setText(result);
    ui->errorLabel->clear(); // Очистить сообщение об ошибке
}

void MainWindow::on_addRandButton_clicked()
{
    QString text = ui->arrayInputTextEdit->toPlainText();
    int rand = QRandomGenerator::global()->bounded(100);
    ui->arrayInputTextEdit->setText(text + " " + QString::number(rand));
}
