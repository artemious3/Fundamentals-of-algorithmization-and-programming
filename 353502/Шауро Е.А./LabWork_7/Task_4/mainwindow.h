#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>

#include "UniverseHT.h"
#include "ModuleHT.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_createButton_clicked();

    void on_findButton_clicked();

    void on_adButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable* mainTable;
    void updateTable();

};
#endif // MAINWINDOW_H
