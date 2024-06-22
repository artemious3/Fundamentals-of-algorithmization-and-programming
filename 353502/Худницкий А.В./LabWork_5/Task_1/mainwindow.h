#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "keyboard.h"
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextCursor>
#include <QTimer>
#include <QTime>
#include <QTextCharFormat>
#include <QStringList>
#include <QDebug>

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
    void virtual mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void on_actionOpen_triggered();

    void takeText(QChar simb);

    void checkText();

    void on_pushButton_clicked();

    void on_stopButton_clicked();

    void on_clearButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_progressBar_valueChanged(int value);

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
