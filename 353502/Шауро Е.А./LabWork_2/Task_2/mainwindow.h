#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QString>

#include "calculatepairs.h"
#include "couplemaker.h"

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

  void on_addRadioButton_clicked();

  void on_changeRadioButton_clicked();

  void on_OpenAction_triggered();

  void on_SaveAction_triggered();

  void on_deleteButton_clicked();

  void on_addButton_clicked();

  void on_findButton_clicked();

  void on_changeButton_clicked();

  void on_calcPosibblePairsButton_clicked();

 private:
  Ui::MainWindow* ui;
  CalculatePairs listOfPartners;
  CoupleMaker helperParticipant;
  QList<CoupleMaker> couples;

  void addToTable();
  void addToTable(const QList<CoupleMaker>& people);

  void changeTable(const CoupleMaker& person, int index);
};
#endif  // MAINWINDOW_H
