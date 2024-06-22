#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QLabel>
#include "sorts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Vector_clicked();

    void on_MergeSort_clicked();

    void on_HeapSort_clicked();

    void on_QuickSort_clicked();

    void on_InterpolationSort_clicked();

    void on_NumberButton_clicked();

private:
    Ui::MainWindow *ui;
    Sorts *sorts;
    QElapsedTimer timer;
    QLabel *label;
};

#endif // MAINWINDOW_H
