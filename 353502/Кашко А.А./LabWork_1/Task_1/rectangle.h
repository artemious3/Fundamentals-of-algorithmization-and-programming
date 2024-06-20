#pragma once

#include <QtWidgets>
#include "movement.h"

class rectangle : public QWidget, private movement {
public:
    explicit rectangle(QWidget *pobj = nullptr);
protected:
    void paintEvent(QPaintEvent* pe);

private:
    QPointF *f = new QPointF;
};
