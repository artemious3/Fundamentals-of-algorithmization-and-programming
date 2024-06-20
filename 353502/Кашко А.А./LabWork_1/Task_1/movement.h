#pragma once

#include <QPoint>

class movement {

protected:

    static void Left(QPointF *point, qreal x);
    static void Right(QPointF *point, qreal x);
};
