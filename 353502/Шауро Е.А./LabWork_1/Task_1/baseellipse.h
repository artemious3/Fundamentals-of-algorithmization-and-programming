#pragma once
#include <QWidget>
#include <QPainter>

class BaseEllipse: public QWidget
{
public:
   BaseEllipse(QWidget *pointer = nullptr);

private:
    QPointF *f = new QPointF;

protected:
    virtual void paintEvent(QPaintEvent *event);
    void up(QPointF *point, double y);
    void down(QPointF *point, double y);

};

