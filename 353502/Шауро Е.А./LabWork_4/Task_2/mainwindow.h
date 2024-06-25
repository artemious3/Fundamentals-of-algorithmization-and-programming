#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <QRandomGenerator>
#include <algorithm>
#include <cmath>

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

    void on_pushButton_clicked();

    void on_sortButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    void printArray(const QVector<int>& arr, int step);
    void interpolationSort(QVector<int>& arr);
    int binarySearch(const QVector<int>& arr, int val, int low, int high);
};

#endif // MAINWINDOW_H
