#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QStandardItemModel>
#include "hashtable.h"

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
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_seeButton_clicked();

    void on_doButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable* myHashTable;
    void updateTable();
};
#endif // MAINWINDOW_H
