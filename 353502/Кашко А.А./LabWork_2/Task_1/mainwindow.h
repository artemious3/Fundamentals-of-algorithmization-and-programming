#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include "functionforworkwithdate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    void loadFileToTable(const QString &filePath);
    void calculateDaysDifference();

    FunctionForWorkWithDate *functionForWorkWithDate;
};
#endif // MAINWINDOW_H
