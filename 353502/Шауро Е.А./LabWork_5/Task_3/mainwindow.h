#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include "bits.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_getIndexButton_clicked();

  void on_allButton_clicked();

  void on_anyButton_clicked();

  void on_countButton_clicked();

  void on_flipButton_clicked();

  void on_resetButton_clicked();

  void on_noneButton_clicked();

  void on_flipindexButton_clicked();

  void on_setButton_clicked();

  void on_set_indexButton_clicked();

  void on_getSizeButton_clicked();

  void on_testButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::MainWindow* ui;
  Bits* myBits;
  QString setRepresent();
};
#endif  // MAINWINDOW_H
