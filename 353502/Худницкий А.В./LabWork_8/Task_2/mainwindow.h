#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include "ArrayHeap.h"
#include "ListHeap.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_popButton_clicked();

    void on_pushButton_clicked();

    void on_popButton_2_clicked();

private:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    ArrayHeap<int> heap;
    ListHeap<int> heap2;
};
#endif // MAINWINDOW_H
