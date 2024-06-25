#ifndef GEMSITEM_H
#define GEMSITEM_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QWidget>
#include "M3_const.h"

class GemsItem : public QWidget, public QGraphicsPixmapItem {
  Q_OBJECT
 public:
  explicit GemsItem();
  int getpRow() const;
  void setpRow(int value);
  int getpCol() const;
  void setpCol(int value);
  int getType() const;
  void setType(int value);
  bool getIsBackground() const;

private:
  int type;
  int pRow;
  int pCol;
  bool isBackground;
  QPropertyAnimation* fstAnim;
  QPropertyAnimation* scndAnim;
};

#endif  // GEMSITEM_H
