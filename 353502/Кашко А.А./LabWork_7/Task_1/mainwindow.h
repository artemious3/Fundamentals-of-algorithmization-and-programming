#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "queue.h"

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
    void on_splitButton_clicked();

    void on_showButton_clicked();

    void on_enqueueButton_clicked();

    void on_dequeueButton_clicked();

    void on_isEmptyButton_clicked();

    void on_showUpdateButton_clicked();

private:
    Ui::MainWindow *ui;
    Queue sourceQueue; // исходная очередь
    Queue negativeQueue; // очередь с отрицательными числами
    Queue positiveQueue; // очередь с положительными числами
};

#endif // MAINWINDOW_H
