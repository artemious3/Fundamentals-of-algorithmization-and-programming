#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Matheric.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QString printMatheric(Matheric& matheric);
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

 private:
  Ui::MainWindow* ui;

 private slots:
  void slot1();
  void slot2();
  void slot3();
  void slot4();
};
#endif  // MAINWINDOW_H
