#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "derivedhashtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createHashTableButton_clicked();
    void on_insertElementButton_clicked();
    void on_findMaxStackButton_clicked();
    void on_printHashTableButton_clicked();
    void on_removeElementButton_clicked();
    void on_findButton_clicked();
    void on_isEmptyButton_clicked();
    void on_sizeButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    DerivedHashTable *hashTable;
};

#endif // MAINWINDOW_H

