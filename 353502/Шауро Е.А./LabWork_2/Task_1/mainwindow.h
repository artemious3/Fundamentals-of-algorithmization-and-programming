#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include "date.h"

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

  void on_Openaction_triggered();

  void on_Saveasaction_triggered();

  void on_NextDayButton_clicked();

  void on_PreviosDayButton_clicked();

  void on_IsLeapButton_clicked();

  void on_WeekNumberButton_clicked();

  void on_DurationButton_clicked();

  void on_selectButton_clicked();

  void on_DaysTillBDButton_clicked();

  void on_addButton_clicked();

  void on_deleteButton_clicked();

  void on_updateButton_clicked();

 private:
  Ui::MainWindow* ui;
  QList<QDate> dateList;
  Date helperDate;
  QDate birthdayDate;

  const int COLUMN_WIDTH = 147;
  const int COLUMN_COUNT = 7;

  const int FIRST_COLUMN = 1;
  const int SECOND_COLUMN = 2;
  const int THIRD_COLUMN = 3;
  const int FORTH_COLUMN = 4;
  const int FIFTH_COLUMN = 5;
  const int SIXTH_COLUMN = 6;

  const int WINDOW_LENGTH = 1350;
  const int WINDOW_WIDTH = 700;

  const int MY_BD_YEAR = 2006;
  const int MY_BD_MONTH = 9;
  const int MY_BD_DAY = 15;

  bool wasFileOpen = false;
};
#endif  // MAINWINDOW_H
