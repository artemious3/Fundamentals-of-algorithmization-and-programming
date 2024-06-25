#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include "form.h"
#include "string.h"

QT_BEGIN_NAMESPACE

static const int MAX_LENGTH = 50;
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
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

  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_checkPunctsButton_clicked();

  void on_action_3_triggered();

  void on_chooseButtojn_clicked();

  void textSaving();

  void arrSaving();

  void structSaving();

  void saveToBinary();

  void sentSaving();

  void readFromBinary();

  void readTextFromFile(QString filename);

  void readArrayFromFile();

  void readStructFromFile();

 private:
  Ui::MainWindow* ui;
};
#endif  // MAINWINDOW_H
