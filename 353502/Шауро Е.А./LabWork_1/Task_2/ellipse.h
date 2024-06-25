#ifndef Ellipse_H
#define Ellipse_H

#include "standart.h"

class Ellipse: public Standart
{

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
//    QPolygonF boundingPolygon() const;

  int myY = 100;
      QRectF boundingRect() const override;
};

#endif // Ellipse_H
