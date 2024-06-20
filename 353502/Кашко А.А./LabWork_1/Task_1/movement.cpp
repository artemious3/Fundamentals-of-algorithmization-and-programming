#include "movement.h"

void movement::Left(QPointF *point, qreal x) {
    point->rx() -= x;
}

void movement::Right(QPointF *point, qreal x) {
    point->rx() += x;
}
