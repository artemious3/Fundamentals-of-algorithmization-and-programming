#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QElapsedTimer>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sortButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> array;
    QVector<int> sortedArray;
    void heapify(QVector<int> &arr, int n, int i);
    void heapSort(QVector<int> &arr);
    void quickSort(QVector<int> &arr, int low, int high);
    void mergeSort(QVector<int> &arr, int l, int r);
    void merge(QVector<int> &arr, int l, int m, int r);
    int partition(QVector<int> &arr, int low, int high);
    int binsearch(QVector<int> &arr, int digit);
    QString arrToString(const QVector<int> &arr);
};

#endif // MAINWINDOW_H
