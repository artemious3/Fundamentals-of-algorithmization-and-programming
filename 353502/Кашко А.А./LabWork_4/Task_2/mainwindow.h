#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include <cmath>

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
    void sortArray();
    void searchElement();

private:
    Ui::MainWindow *ui;
    void printArray(const std::vector<int>& arr, int step);
    void interpolationSort(std::vector<int>& arr);
    int binarySearch(const std::vector<int>& arr, int val, int low, int high);
    bool validateInput(const QString &input);
};

#endif // MAINWINDOW_H
