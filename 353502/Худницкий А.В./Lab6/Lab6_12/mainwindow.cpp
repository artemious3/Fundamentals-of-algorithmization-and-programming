#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QMessageBox>

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
    Shop shop1 = {1, 100000.50, '1', true};

    QString info1;
    info1 += QString::number(shop1.id) + " | "
            + QString::number(shop1.revenue) + " | "
            + QString::number(shop1.number) + " | "
            + (shop1.isOpen ? "Open" : "Closed") + " | "
            + Shop::name + " | ";
    for (int item : Shop::stock) {
        info1 += QString::number(item) + " ";
    }
    info1 += "\n";
    ui->textEdit->append(info1);

    Shop shop2;
    shop2.id = 2;
    shop2.revenue = 200000.75;
    shop2.number = '2';
    shop2.isOpen = false;

    QString info2;
    info2 += QString::number(shop2.id) + " | "
            + QString::number(shop2.revenue) + " | "
            + QString::number(shop2.number) + " | "
            + (shop2.isOpen ? "Open" : "Closed") + " | "
            + Shop::name + " | ";
    for (int item : Shop::stock) {
        info2 += QString::number(item) + " ";
    }
    info2 += "\n";
    ui->textEdit->append(info2);

    Shop shop3;
    shop3.id = ui->lineEdit->text().toInt();
    shop3.revenue = ui->lineEdit_2->text().toDouble();
    shop3.number = ui->lineEdit_3->text().toInt();
    shop3.isOpen = ui->lineEdit_4->text().toInt() != 0;

    QString info3;
    info3 += QString::number(shop3.id) + " | "
             + QString::number(shop3.revenue) + " | "
             + QString::number(shop3.number) + " | "
             + (shop3.isOpen ? "Open" : "Closed") + " | "
             + Shop::name + " | ";
    for (int item : Shop::stock) {
        info3 += QString::number(item) + " ";
    }
    info3 += "\n";
    ui->textEdit->append(info3);

    Shop shop4;
    Shop* ptr = &shop4;
    ptr->id = 4;
    ptr->revenue = 400000.0;
    ptr->number = '4';
    ptr->isOpen = true;

    QString info4;
    info4 += QString::number(shop4.id) + " | "
             + QString::number(shop4.revenue) + " | "
             + QString::number(shop4.number) + " | "
             + (shop4.isOpen ? "Open" : "Closed") + " | "
             + Shop::name + " | ";
    for (int item : Shop::stock) {
        info4 += QString::number(item) + " ";
    }
    info4 += "\n";
    ui->textEdit->append(info4);

    Shop shop5;
    Shop& ref = shop5;
    ref.id = 5;
    ref.revenue = 500000.25;
    ref.number = '5';
    ref.isOpen = false;

    QString info5;
    info5 += QString::number(shop5.id) + " | "
             + QString::number(shop5.revenue) + " | "
             + QString::number(shop5.number) + " | "
             + (shop5.isOpen ? "Open" : "Closed") + " | "
             + Shop::name + " | ";
    for (int item : Shop::stock) {
        info5 += QString::number(item) + " ";
    }
    info5 += "\n";
    ui->textEdit->append(info5);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString text = ui->textEdit->toPlainText();
    QString filename = "ХудницкийЛаб20.txt";

    std::ofstream outFile(filename.toStdString());
    if (!outFile.is_open()) {
        QMessageBox::critical(this, "Error", "Unable to open file for writing.");
        return;
    }
    outFile << text.toStdString();
    outFile.close();

    std::ifstream inFile(filename.toStdString());
    if (!inFile.is_open()) {
        QMessageBox::critical(this, "Error", "Unable to open file for reading.");
        return;
    }

    QString fileText;
    std::string line;
    while (std::getline(inFile, line)) {
        fileText += QString::fromStdString(line) + "\n";
    }
    inFile.close();

    ui->textEdit->setPlainText(fileText);
}

void MainWindow::on_pushButton_3_clicked()
{
    Shop shopx;
    shopx.id = ui->lineEdit->text().toInt();
    shopx.revenue = ui->lineEdit_2->text().toDouble();
    shopx.number = ui->lineEdit_3->text().toInt();
    shopx.isOpen = ui->lineEdit_4->text().toInt() != 0;

    std::ifstream inFile("ХудницкийЛаб20_1.txt");
    if (!inFile.is_open() || inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Файл не существует или пуст.\n";
    } else {
        QString fileText;
        char ch;
        while (inFile.get(ch)) {
            fileText.append(QChar(ch));
        }
        inFile.close();

        ui->textEdit->setPlainText(fileText);
    }

    std::ofstream outFile("ХудницкийЛаб20_1.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << shopx.id << '|'
                << shopx.revenue << '|'
                << shopx.number << '|'
                << shopx.isOpen << '\n';
        outFile.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }

    std::ifstream inBinFile("ХудницкийЛаб20_2.bin", std::ios::binary);
    if (!inBinFile.is_open()) {
        std::cerr << "Файл не существует или не удается открыть.\n";
    } else {
        Shop shopRead;
        QString fileText;
        while (inBinFile.read(reinterpret_cast<char*>(&shopRead.id), sizeof(shopRead.id))) {
            inBinFile.read(reinterpret_cast<char*>(&shopRead.revenue), sizeof(shopRead.revenue));
            inBinFile.read(reinterpret_cast<char*>(&shopRead.number), sizeof(shopRead.number));
            inBinFile.read(reinterpret_cast<char*>(&shopRead.isOpen), sizeof(shopRead.isOpen));

            fileText += QString("ID: %1 | Revenue: %2 | Number: %3 | Is Open: %4\n")
                        .arg(shopRead.id)
                        .arg(shopRead.revenue)
                        .arg(shopRead.number)
                        .arg(shopRead.isOpen);
        }
        inBinFile.close();

    std::ofstream outBinFile("ХудницкийЛаб20_2.bin", std::ios::binary | std::ios::app);
    if (outBinFile.is_open()) {
        outBinFile.write(reinterpret_cast<const char*>(&shopx.id), sizeof(shopx.id));
        outBinFile.write(reinterpret_cast<const char*>(&shopx.revenue), sizeof(shopx.revenue));
        outBinFile.write(reinterpret_cast<const char*>(&shopx.number), sizeof(shopx.number));
        outBinFile.write(reinterpret_cast<const char*>(&shopx.isOpen), sizeof(shopx.isOpen));
        outBinFile.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }

    ui->textEdit->setPlainText(fileText);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString text = ui->textEdit->toPlainText();

    std::wofstream file1("ХудницкийЛаб20_3.txt", std::ios::binary);
    if (!file1.is_open()) {
        std::wcerr << L"Не удалось открыть файл для записи.\n";
        return;
    }
    for (const QChar& qch : text) {
        wchar_t ch = static_cast<wchar_t>(qch.unicode());
        file1.put(ch);
    }
    file1.close();

    std::wifstream file2("ХудницкийЛаб20_3.txt", std::ios::binary);
    if (!file2.is_open() || file2.peek() == std::wifstream::traits_type::eof()) {
        std::wcerr << L"Файл не существует или пуст.\n";
        return;
    }
    QString fileText;
    wchar_t ch;
    while (file2.get(ch)) {
        fileText.append(ch);
    }
    file2.close();

    ui->textEdit->setText(fileText);
}

void MainWindow::on_pushButton_5_clicked()
{
    close();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit->clear();
}
