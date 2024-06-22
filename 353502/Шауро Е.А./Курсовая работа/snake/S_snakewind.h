#ifndef S_SNAKEWIND_H
#define S_SNAKEWIND_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>

#include "S_scene.h"
#include "mainwindow.h"

namespace Ui {
class SnakeWind;
}

class SnakeWind : public QMainWindow {
  Q_OBJECT

 public:
  explicit SnakeWind(QWidget* parent = nullptr);
  ~SnakeWind();

 private slots:
  void on_snakeStartButton_clicked();
  void takeSnakeEndSignal();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  Ui::SnakeWind* ui;
  S_Scene* sscene;

 signals:
  void windowClosed();
  void newScoreFromSnake();
};

#endif  // S_SNAKEWIND_H
