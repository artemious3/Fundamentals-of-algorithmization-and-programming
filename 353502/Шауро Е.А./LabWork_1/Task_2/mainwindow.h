#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "circle.h"
#include "star5.h"
#include "star6.h"
#include "star8.h"
#include "hexagon.h"
#include "cross.h"
#include "standart.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();
    Standart *item = nullptr;
    QList<Standart*> items;

    void updatePosLabel(const QPointF &center);
    void updatePerimeterLabel(qreal perimeter);
    void updateSquareLabel(qreal square);
    void updateTypeLabel(Standart *name);

    void plusMinus(Standart *item, qreal con);

    void rePaint(Standart* item, qreal param1, qreal param2, qreal param3);

    void hideButtons();

    void changes();


private slots:
    void on_TriangleButton_clicked();
    void on_CircleButton_clicked();
    void on_RhombusButton_clicked();
    void on_SquareButton_clicked();
    void on_RectButton_clicked();
    void on_Star5Button_clicked();
    void on_Star6Button_clicked();
    void on_Star8Button_clicked();
    void on_HexButton_clicked();
    void on_CrossButton_clicked();


    void on_UpdateButton_clicked();
    void on_UpdateButton_2_clicked();

    void on_BackButton_clicked();
    void on_NextButton_clicked();

    void on_PlussButton_clicked();
    void on_MinusButton_clicked();

    void on_PosSlider_valueChanged(int value);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
