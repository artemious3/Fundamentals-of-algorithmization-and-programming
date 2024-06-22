#ifndef BIRDWIND_H
#define BIRDWIND_H

#include <QCloseEvent>
#include <QMainWindow>
#include "B_scene.h"

#include "mainwindow.h"

namespace Ui {
class BirdWind;
}

class BirdWind : public QMainWindow {
  Q_OBJECT

 public:
  explicit BirdWind(QWidget* parent = nullptr);
  ~BirdWind() override;

 private slots:
  void on_startBirdButton_clicked();
  void takeBirdEndSignal();

 private:
  Ui::BirdWind* ui;
  B_Scene* bscene;
  int intervalScore;

 protected:
  void closeEvent(QCloseEvent* event) override;

signals:
    void windowClosed();
    void newScoreFromBird();


};

#endif  // BIRDWIND_H
