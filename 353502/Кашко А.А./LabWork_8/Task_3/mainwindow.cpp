#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "redblacktree.h"
#include <QRandomGenerator>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map.clear();
    set.clear();
    for (int i = 0; i < 5; ++i) {
        set.insert(QRandomGenerator::global()->bounded(100));
        map.insert(QRandomGenerator::global()->bounded(100), QRandomGenerator::global()->bounded(100));
    }

    ui->mapTable->horizontalHeader()->setStretchLastSection(true);

    displayMap();
    displaySet();

    setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMap()
{
    ui->mapTable->clear();
    ui->mapTable->setRowCount(map.size());
    ui->mapTable->setColumnCount(2);
    QStringList headers;
    headers << "Ключ" << "Значение";
    ui->mapTable->setHorizontalHeaderLabels(headers);

    int i = 0;
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        ui->mapTable->setItem(i, 0, new QTableWidgetItem(QString::number(it.key())));
        ui->mapTable->setItem(i, 1, new QTableWidgetItem(QString::number(it.value())));
        ++i;
    }
}

void MainWindow::displaySet()
{
    QString text = "";
    for (auto it = set.constBegin(); it != set.constEnd(); ++it) {
        text += QString::number(*it) + " ";
    }
    ui->setLabel->setText(text.trimmed());
}

void MainWindow::on_mapInsertButton_clicked()
{
    map.insert(ui->keySpinBox->value(), ui->valSpinBox->value());
    displayMap();
}

void MainWindow::on_mapRemoveButton_clicked()
{
    map.remove(ui->keySpinBox->value());
    displayMap();
}

void MainWindow::on_mapContainsButton_clicked()
{
    ui->mapResLabel->setText(map.contains(ui->keySpinBox->value()) ? "ДА" : "НЕТ");
}

void MainWindow::on_mapClearButton_clicked()
{
    map.clear();
    displayMap();
}

void MainWindow::on_setInsertButton_clicked()
{
    set.insert(ui->setValSpinBox->value());
    displaySet();
}

void MainWindow::on_setRemoveButton_clicked()
{
    set.remove(ui->setValSpinBox->value());
    displaySet();
}

void MainWindow::on_setContainsButton_clicked()
{
    ui->setResLabel->setText(set.contains(ui->setValSpinBox->value()) ? "ДА" : "НЕТ");
}

void MainWindow::on_setClearButton_clicked()
{
    set.clear();
    displaySet();
}

void MainWindow::on_pushButton_clicked()
{
    RedBlackTree<int, int>* tree = new RedBlackTree<int, int>();
    tree->printTree(ui->label_8);
}

