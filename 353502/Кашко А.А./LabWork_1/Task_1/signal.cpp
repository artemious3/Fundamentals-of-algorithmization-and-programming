#include "signal.h"
#include "movement.h"

signal::signal(QWidget *) {
    *f = {30, 100};
    *F = {30, 60};
    *t = {0, 60};
}

void signal::paintEvent(QPaintEvent *pe) {
    static bool was = true;
    static bool WAS = true;
    static bool T = true;

    QWidget::paintEvent(pe);
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    painter.drawRect(100, 100, 50, 60);

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawRect(100, 160, 50, 10);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(100, 170, 20, 50);
    painter.drawRect(130, 170, 20, 50);

    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(105, 59, 40, 40);

    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    painter.drawRect(150, 100, 10, 70);
    painter.drawRect(int(f->rx()), int(f->ry()), 70, 10);
    if (f->rx() > 30 && f->rx() <= 60) {
        was ? movement::Left(f, 0.015) : movement::Right(f, 0.015);
    }
    else {
        if (was) f->rx() = 31;
        else f->rx() = 59;
        was = !was;
    }

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(int(F->rx()), 60, 5, 50);
    if (F->rx() > 30 && F->rx() <= 60) {
        WAS ? movement::Left(F, 0.015) : movement::Right(F, 0.015);
    } else {
        if (WAS) F->rx() = 31;
        else F->rx() = 59;
        WAS = !WAS;
    }

    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawRect(int(t->rx()), 60, 30, 15);
    if (t->rx() > 0 && t->rx() <= 30) {
        T ? movement::Left(t, 0.015) : movement::Right(t, 0.015);
    } else {
        if (T) t->rx() = 1;
        else t->rx() = 29;
        T = !T;
    }




    update();
}
