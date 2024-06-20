#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
#include <QString>
#include <QPushButton>
#include <QSpinBox>
#include <QTextBrowser>
#include <QLabel>
#include <chrono>
#include "hashtable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void insertInHash16();
    void insertInHash64();
    void insertInHash128();
    void insertInHash2048();
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable hash16 = HashTable(16);
    HashTable hash64 = HashTable(64);
    HashTable hash128 = HashTable(128);
    HashTable hash2048 = HashTable(2048);

    void demonstrateHash16();
    void demonstrateHash64();
    void demonstrateHash128();
    void demonstrateHash2048();
};

#endif // MAINWINDOW_H
