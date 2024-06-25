#pragma once

#include <QtWidgets>
#include "movement.h"

class signal : public QWidget, private movement {
public:
    explicit signal(QWidget *pobj = nullptr);
protected:
    void paintEvent(QPaintEvent* pe);
private:
    QPointF *f = new QPointF;
    QPointF *F = new QPointF;
    QPointF *t = new QPointF;
};
