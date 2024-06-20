#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::insertInHash16);
    connect(ui->addButton64, &QPushButton::clicked, this, &MainWindow::insertInHash64);
    connect(ui->addButton128, &QPushButton::clicked, this, &MainWindow::insertInHash128);
    connect(ui->addButton2048, &QPushButton::clicked, this, &MainWindow::insertInHash2048);

    int temp = 0;
    srand(time(nullptr));
    for (int i = 0; i < 10; ++i)
    {
        temp = 1 + rand() % 100;
        QString key = QString::number(temp);
        hash16.insertItem(key, temp);
        hash64.insertItem(key, temp);
        hash128.insertItem(key, temp);
        hash2048.insertItem(key, temp);
    }

    demonstrateHash16();
    demonstrateHash64();
    demonstrateHash128();
    demonstrateHash2048();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertInHash16()
{
    int key = ui->keySpinBox->value();
    int value = ui->valueSpinBox->value();
    QString strKey = QString::number(key);
    hash16.insertItem(strKey, value);

    demonstrateHash16();
}

void MainWindow::insertInHash64()
{
    int key = ui->keySpinBox->value();
    int value = ui->valueSpinBox->value();
    QString strKey = QString::number(key);
    hash64.insertItem(strKey, value);

    demonstrateHash64();
}

void MainWindow::insertInHash128()
{
    int key = ui->keySpinBox->value();
    int value = ui->valueSpinBox->value();
    QString strKey = QString::number(key);
    hash128.insertItem(strKey, value);

    demonstrateHash128();
}

void MainWindow::insertInHash2048()
{
    int key = ui->keySpinBox->value();
    int value = ui->valueSpinBox->value();
    QString strKey = QString::number(key);
    hash2048.insertItem(strKey, value);

    demonstrateHash2048();
}

void MainWindow::demonstrateHash16()
{
    QString answer = "";
    QVector<QPair<QString, int>> vec = hash16.displayHash();
    for (int i = 0; i < vec.size(); ++i)
    {
        answer += QString::number(i+1) + ": ";
        answer += vec[i].first + " ";
        answer += QString::number(vec[i].second) + "\n";
    }

    ui->demonstratingBrowser->setText(answer);
}

void MainWindow::demonstrateHash64()
{
    QString answer = "";
    QVector<QPair<QString, int>> vec = hash64.displayHash();
    for (int i = 0; i < vec.size(); ++i)
    {
        answer += QString::number(i+1) + ": ";
        answer += vec[i].first + " ";
        answer += QString::number(vec[i].second) + "\n";
    }

    ui->demonstratingBrowser64->setText(answer);
}

void MainWindow::demonstrateHash128()
{
    QString answer = "";
    QVector<QPair<QString, int>> vec = hash128.displayHash();
    for (int i = 0; i < vec.size(); ++i)
    {
        answer += QString::number(i+1) + ": ";
        answer += vec[i].first + " ";
        answer += QString::number(vec[i].second) + "\n";
    }

    ui->demonstratingBrowser128->setText(answer);
}

void MainWindow::demonstrateHash2048()
{
    QString answer = "";
    QVector<QPair<QString, int>> vec = hash2048.displayHash();
    for (int i = 0; i < vec.size(); ++i)
    {
        answer += QString::number(i+1) + ": ";
        answer += vec[i].first + " ";
        answer += QString::number(vec[i].second) + "\n";
    }

    ui->demonstratingBrowser2048->setText(answer);
}

void MainWindow::on_searchButton_clicked()
{
    int key = ui->searchKeySpinBox->value();
    QString strKey = QString::number(key);

    auto start16 = std::chrono::high_resolution_clock::now();
    int result16 = hash16.searchItem(strKey);
    auto end16 = std::chrono::high_resolution_clock::now();

    auto start64 = std::chrono::high_resolution_clock::now();
    int result64 = hash64.searchItem(strKey);
    auto end64 = std::chrono::high_resolution_clock::now();

    auto start128 = std::chrono::high_resolution_clock::now();
    int result128 = hash128.searchItem(strKey);
    auto end128 = std::chrono::high_resolution_clock::now();

    auto start2048 = std::chrono::high_resolution_clock::now();
    int result2048 = hash2048.searchItem(strKey);
    auto end2048 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration16 = end16 - start16;
    std::chrono::duration<double, std::micro> duration64 = end64 - start64;
    std::chrono::duration<double, std::micro> duration128 = end128 - start128;
    std::chrono::duration<double, std::micro> duration2048 = end2048 - start2048;

    QString resultText = "";
    if (result16 != -1) {
        resultText += "Значение найдено в Hash16, время: " + QString::number(duration16.count()) + " мкс.\n";
    } else {
        resultText += "Значение не найдено в Hash16, время: " + QString::number(duration16.count()) + " мкс.\n";
    }

    if (result64 != -1) {
        resultText += "Значение найдено в Hash64, время: " + QString::number(duration64.count()) + " мкс.\n";
    } else {
        resultText += "Значение не найдено в Hash64, время: " + QString::number(duration64.count()) + " мкс.\n";
    }

    if (result128 != -1) {
        resultText += "Значение найдено в Hash128, время: " + QString::number(duration128.count()) + " мкс.\n";
    } else {
        resultText += "Значение не найдено в Hash128, время: " + QString::number(duration128.count()) + " мкс.\n";
    }

    if (result2048 != -1) {
        resultText += "Значение найдено в Hash2048, время: " + QString::number(duration2048.count()) + " мкс.\n";
    } else {
        resultText += "Значение не найдено в Hash2048, время: " + QString::number(duration2048.count()) + " мкс.\n";
    }

    ui->searchResultLabel->setText(resultText);
}
