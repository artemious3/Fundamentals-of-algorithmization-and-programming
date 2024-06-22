#ifndef F_FOODCATCHWIND_H
#define F_FOODCATCHWIND_H

#include <QCloseEvent>
#include <QGraphicsPixmapItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "F_scene.h"
#include "mainwindow.h"

namespace Ui {
class FoodCatchWind;
}

class FoodCatchWind : public QMainWindow {
  Q_OBJECT

 public:
  explicit FoodCatchWind(QWidget* parent = nullptr);
  ~FoodCatchWind();

 private slots:
  void on_startFoodCatGameButton_clicked();
  void takeFoodCatEndSignal();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  Ui::FoodCatchWind* ui;
  QTimer* timer;
  F_Scene* fscene;

 signals:
  void windowClosed();
  void newScoreFromFoodCat();
};

#endif  // F_FOODCATCHWIND_H
