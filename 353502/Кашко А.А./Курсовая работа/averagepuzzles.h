#ifndef AVERAGEPUZZLES_H
#define AVERAGEPUZZLES_H

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

#include "graphicsscene.h"
#include "puzzlethemes.h"

namespace Ui {
class AveragePuzzles;
}

class AveragePuzzles : public QDialog
{
    Q_OBJECT

public:
    explicit AveragePuzzles(QWidget *parent = nullptr);
    ~AveragePuzzles();

protected:
    bool eventFilter(QObject* obj, QEvent *ev) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_buttton_NextLevelHard_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

public:
    void themesPuzzle(int choise);

private:
    Ui::AveragePuzzles *ui;

    QList<QImage> splitImage(const QString& filename);
    void swapImageParts();
    void checkPositions();

    int themes = 0; int dop =0;
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

#endif // AVERAGEPUZZLES_H
