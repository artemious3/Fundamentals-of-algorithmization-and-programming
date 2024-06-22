#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pet.h"
#include "mainConst.h"

class MainScene : public QGraphicsScene
{
public:
    MainScene();
    void updateProgressBar();
};

#endif // MAINSCENE_H
