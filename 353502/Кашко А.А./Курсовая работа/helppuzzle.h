#ifndef HELPPUZZLE_H
#define HELPPUZZLE_H

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
#include "helpforplayer.h"

namespace Ui {
class HelpPuzzle;
}

class HelpPuzzle : public QDialog
{
    Q_OBJECT

public:
    explicit HelpPuzzle(QWidget *parent = nullptr);
    ~HelpPuzzle();

private slots:
    void on_button_StartGame_clicked();

    void on_button_ClosePlay_clicked();

    void on_button_BackHomeScreen_clicked();

    void on_button_NextPuzzle_clicked();

    void on_button_HelpUser_clicked();

    void on_button_NextLevelHard_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    bool eventFilter(QObject* obj, QEvent *ev) override;

public:
    void themesPuzzle(int choise);

private:
    Ui::HelpPuzzle *ui;

    QList<QImage> splitImage(const QString& filename);
    void swapImageParts();
    void checkPositions();

    int themes = 0; int dop = 0; // переменная для определения темы и переключения пазлов
    QSet<int> correctPartsSet;
    QGraphicsScene *scene = nullptr;
    QTimer *timer = nullptr;
    QMap<int, QPointF> partPositions;
    QMap<QGraphicsPixmapItem*, int> indexes;
    QGraphicsPixmapItem *selectedItem = nullptr;
    QString filename;
    QList<QImage> imageParts;
    QGraphicsPixmapItem *pixmapItem;
    int num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int answer;
};

#endif // HELPPUZZLE_H
