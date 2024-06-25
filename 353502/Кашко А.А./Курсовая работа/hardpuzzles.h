#ifndef HARDPUZZLES_H
#define HARDPUZZLES_H

#include <QDialog>
#include <QMainWindow>
#include <QImage>
#include <QRect>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QTimer>
#include <random>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QTransform>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "graphicsscene.h"
#include "puzzlethemes.h"
#include "mainwindow.h"

namespace Ui {
class HardPuzzles;
}

class HardPuzzles : public QDialog
{
    Q_OBJECT

public:
    explicit HardPuzzles(QWidget *parent = nullptr);
    ~HardPuzzles();

protected:
    bool eventFilter(QObject* obj, QEvent *ev) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

public:
    void themesPuzzle(int choise);

private:
    Ui::HardPuzzles *ui;

    QList<QImage> splitImage(const QString& filename);
    void swapImageParts();
    void checkPositions();

    int themes = 0; int dop = 0;
    QSet<int> correctPartsSet;
    QGraphicsScene *scene = nullptr;
    QTimer *timer = nullptr;
    QMap<int, QPointF> partPositions;
    QMap<QGraphicsPixmapItem*, int> indexes;
    QGraphicsPixmapItem *selectedItem = nullptr;
    QString filename;
    QList<QImage> imageParts;
    int num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int answer;
};

#endif // HARDPUZZLES_H
