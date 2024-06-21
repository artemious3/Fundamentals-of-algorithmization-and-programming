#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QString>
#include <QDebug>

#include "Deque.h"

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
    void on_pushBackButton_clicked();

    void on_pushFrontButton_clicked();

    void on_popBackButton_clicked();

    void on_popFrontButton_clicked();

    void on_emptyButton_clicked();

    void on_clearButton_clicked();

    void on_sizeButton_clicked();

private:
    Ui::MainWindow *ui;
    Deque<int> deque;
    void updateTextBrowser();
};
#endif // MAINWINDOW_H
