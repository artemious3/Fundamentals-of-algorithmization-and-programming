#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mapInsertButton_clicked();
    void on_mapRemoveButton_clicked();
    void on_mapContainsButton_clicked();
    void on_mapClearButton_clicked();
    void on_setInsertButton_clicked();
    void on_setRemoveButton_clicked();
    void on_setContainsButton_clicked();
    void on_setClearButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMap<int, int> map;
    QSet<int> set;

    void displayMap();
    void displaySet();
};

#endif // MAINWINDOW_H
