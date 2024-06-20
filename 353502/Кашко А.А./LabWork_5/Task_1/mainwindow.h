#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextCursor>
#include <QTimer>
#include <QTime>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QStringList>
#include <QDebug>
#include "const.h"
#include "keyboard.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void mousePressEvent();

private slots:
    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void takeText(QChar simb);

    void checkText();

    void on_pushButton_clicked();

    void on_stopButton_clicked();

    void on_clearButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow* ui;
    Keyboard* keyboard;
    QString textForSet;
    QString exampleText;
    QTimer* timer;
    QTime startTime;
    int elapsed;
    int progBarValue;

    void updateTime();
};
#endif  // MAINWINDOW_H
