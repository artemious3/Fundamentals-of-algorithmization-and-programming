#ifndef MAINCONST_H
#define MAINCONST_H
#include <QPointF>
#include "iostream"
static const int HOME_SIZE = 1000;
static const int INFO_SIZE = 610;
static const int START_SC_RECT_X = -450;
static const int START_SC_RECT_Y = START_SC_RECT_X;
static const int SNAKE_INTERVAL = 1000;
static const int MATCH3_INTERVAL = 3000;
static const int FLAPPY_BIRD_INTERVAL = 1500;
static const int FOOD_CATCHER_INTERVAL = 2000;
static const int PET_INTERVAL =
    std::min(std::min(SNAKE_INTERVAL, MATCH3_INTERVAL),
             std::min(FLAPPY_BIRD_INTERVAL, FOOD_CATCHER_INTERVAL));
static const int MAX = 100;
static const int BIRD_BONUS = 10;
static const int SNAKE_BONUS = 5;
static const int MATCH_BONUS = 3;
static const int FOODCAT_BONUS = 5;
static const int PET_SIZE_Y = 300;
static const int PET_SIZE_X = 500;
static const QPointF CENTRAL =
    QPointF(int(HOME_SIZE / 2) - 700, int(HOME_SIZE / 2) - 400);
static const int BEST_STATS = 90;
static const int NORMAL_STATS = 40;
#endif  // MAINCONST_H
