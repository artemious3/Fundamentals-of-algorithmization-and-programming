#ifndef M3_SCENE_H
#define M3_SCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QString>
#include <QTransform>

#include "M3_const.h"
#include "M3_gemsitem.h"
#include "globals.h"

class M3_Scene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit M3_Scene(QObject* parent = nullptr);
  void addGems();
  void setIsBackground(bool value);
  void addScore();
  bool getIsBackground() const;
  int getScore() const;

private:
  int score;
  bool isBackground;

  GemsItem* m_selectedGem;
  GemsItem* gem;

  QPointF startPos;
  GemsItem*** arrOfGems;
  QGraphicsTextItem* scoreText;

  void deleteMatches(GemsItem* gem);
  void swapGems(GemsItem* gem1, GemsItem* gem2);
  void checkHorMatches();
  void checkVertMatches();
  void dropGems();

 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // M3_SCENE_H
