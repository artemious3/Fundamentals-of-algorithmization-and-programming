#ifndef S_CONST_H
#define S_CONST_H
#include <QPointF>

static const int APPLE_SIZE = 50;
static const int SNAKE_SIZE = 70;
static const int START_POS = 100;
static const int STEP = 70;
static const int APPLE_BORDER = 50;
static const int SCENE_RECT = 950;
static const int WINDOW_LENGTH = SCENE_RECT + 20;
static const int WINDOW_WIDTH = SCENE_RECT + 150;
static const int TIME = 200;
static const int FONT_HIGH = 30;
static const int GAME_OVER_SIZE = 500;
static const QPointF TEXT_POINT = QPointF(0, 50);

enum Direction { leftTurn, rightTurn, up, down, none };

#endif // S_CONST_H
