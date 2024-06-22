#ifndef PET_H
#define PET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>

#include "mainConst.h"

enum CatMood { Cool, Standart, Angry, GoAway };

class Pet : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
 public:
  Pet();
  void updateCatIcon();
  CatMood getMood() const;
  void setMood(const CatMood& value);

 private:
  CatMood mood;
};

#endif  // PET_H
