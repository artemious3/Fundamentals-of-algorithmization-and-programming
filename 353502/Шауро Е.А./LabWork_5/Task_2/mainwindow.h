#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "newstring.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

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
    void on_lengthButton_clicked();

    void on_beginButton_clicked();

    void on_endButton_clicked();

    void on_memcpyButtonButton_clicked();

    void on_memmoveButton_clicked();

    void on_strcpyButton_clicked();

    void on_strncpyButton_clicked();

    void on_strcatButton_clicked();

    void on_strncatButton_clicked();

    void on_memcmpButton_clicked();

    void on_strcmpButton_clicked();

    void on_strncmpButton_clicked();

    void on_strcollButton_clicked();

    void on_strxfrmButton_clicked();

    void on_strtokButton_clicked();

    void on_memsetButton_clicked();

    void on_strerrorButton_pressed();

    void on_strerrorButton_clicked();

    void on_strcharButton_clicked();

    void on_strerrorButton_released();

private:
    Ui::MainWindow *ui;
    NewString text;
    NewString secondStr;

    void changeMainText();
    void changeSecondText();
};
#endif // MAINWINDOW_H
