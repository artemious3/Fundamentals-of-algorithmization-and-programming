#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "string.h"

const int MAX_LENGTH = 50;

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

  struct Planet {
    QString name;
    int radius;
    double age;
    float period;
    QChar type;
    bool hasRings;
    char mainChemElement[MAX_LENGTH];
    double maxAndMinTemp[2];
  };

 private slots:

  void on_addButton_clicked();

  void on_showButton_clicked();

 private:
  Ui::MainWindow* ui;

  Planet Planet_initByStr;
  Planet Planet_initByEachField;
  Planet Planet_initByUser;
  Planet Planet_initByPointer;
  Planet* pointer = &Planet_initByPointer;
  Planet Planet_initByRef;
  Planet& ref = Planet_initByRef;

  QString toMyStr(Planet pl);
  QString toMyStr(Planet* pl);
};
#endif  // MAINWINDOW_H
