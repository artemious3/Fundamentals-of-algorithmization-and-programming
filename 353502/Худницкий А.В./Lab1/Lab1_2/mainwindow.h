#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rectangle.h"
#include "figure.h"
#include "square.h"
#include "circle.h"
#include "rhombus.h"
#include "triangle.h"
#include "star5.h"
#include "star6.h"
#include "star8.h"
#include "hexagon.h"
#include "octagon.h"
#include <QGraphicsScene>
#include <QtWidgets>
#include <QTimer>

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

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void changes();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_99_clicked();

private:
    QTimer *timer;

private:
    Ui::MainWindow *ui;
    Base* base;
    QGraphicsScene *scene = new QGraphicsScene();
    QList<Base*> mass;

    void updateSquare(qreal square);
    void updatePerimeter(qreal perimeter);
    void updatePos(const QPointF &center);
};
#endif // MAINWINDOW_H
