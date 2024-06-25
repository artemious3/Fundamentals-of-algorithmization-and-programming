#ifndef BALLOON_H
#define BALLOON_H

#pragma once

#include "baseellipse.h"
#include <QPointF>


class Balloon: public BaseEllipse
{
public:
    Balloon(QWidget *pointer = nullptr);

private:
    QPointF *f = new QPointF;
    bool *flyDown = new bool;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // BALLOON_H



