#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QString>
#include "sick.h"

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

    void on_OpenAction_triggered();

    void on_SaveAction_triggered();

    void on_deleteButton_clicked();

    void on_addButton_2_clicked();

    void on_changeButton_2_clicked();

private:
    QList<QString> sicks;
    QList<QString> helpersick;

    Ui::MainWindow* ui;

    void addToTable();
    void addToTable(const QList<Sick>& people);

    QString CoupleConvertCoupleIntoText(const Sick&, bool);

    void changeTable(const Sick&, int);
};
#endif  // MAINWINDOW_H
