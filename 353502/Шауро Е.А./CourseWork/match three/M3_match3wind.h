#ifndef MATCH3WIND_H
#define MATCH3WIND_H

#include <QCloseEvent>
#include <QMainWindow>

#include "M3_scene.h"
#include "mainwindow.h"

namespace Ui {
class Match3Wind;
}

class Match3Wind : public QMainWindow {
  Q_OBJECT

 public:
  explicit Match3Wind(QWidget* parent = nullptr);
  ~Match3Wind() override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  Ui::Match3Wind* ui;
  M3_Scene* mscene;

 signals:
  void windowClosed();
};

#endif  // MATCH3WIND_H
