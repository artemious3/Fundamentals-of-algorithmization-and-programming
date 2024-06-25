#ifndef CONST_H
#define CONST_H

enum Language{
    ru,
    bel,
    arab,
    ger,
    chin,
    heb,
    en,
    fr
};

static const int MAX_VALUE = 100;
static const int ONE_MIN = 60000;
static const int SPACING = 10;

static const int LENGTH = 1050;
static const int WIDTH = 635;

static const int SCENE_LEN = LENGTH - 15;
static const int SCENE_WIDTH = WIDTH / 2;

static const int BUTTON_LENGTH = 70;
static const int BUTTON_WIDTH = 70;
static const int BIG_BUTTON_LENGTH = 70;

static const int DELETE_PLACE = 13;
static const int TAB_PLACE = 14;
static const int CAPS_PLACE = 26;
static const int ENTER_PLACE = 38;
static const int SHIFT_PLACE = 39;
static const int SPACE_PLACE = 52;

static const int TIME_INTERVAL = 50;

#endif // CONST_H
