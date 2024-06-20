#ifndef PUZZLETIME_H
#define PUZZLETIME_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include "puzzlethemes.h"

namespace Ui {
class PuzzleTime;
}

class PuzzleTime : public QDialog
{
    Q_OBJECT

public:
    explicit PuzzleTime(QWidget *parent = nullptr);
    ~PuzzleTime();

private slots:
    void on_closeButton_clicked();

    void on_pushButton_3_clicked();

    void on_startButton_clicked();

private:
    Ui::PuzzleTime *ui;

    QGraphicsScene *scene = nullptr;
    QString filename;
    QList<QImage> imageParts;
    QMap<QGraphicsPixmapItem*, int> indexes;
    QMap<int, QPointF> partPositions;
    QGraphicsPixmapItem *selectedItem = nullptr;
    QSet<int> correctPartsSet;
    QTimer *timer;
    QTime *time;

    QList<QImage> splitImage(const QString& filename);
    void swapImageParts();
    bool eventFilter(QObject *obj, QEvent *ev);
    void updateTimer();
};

#endif // PUZZLETIME_H
