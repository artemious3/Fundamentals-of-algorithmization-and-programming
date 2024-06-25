#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct City
    {
        int population;                                // население
        double area;                                   // площадь города
        QChar first_letter_country;                    // страна, в которой расположен город
        bool capital;                                  // логическаяя переменная для проверки, является ли город столицей
        static char streets[5][25];                    // названия улиц
        static int number_of_houses[5];                // кол-во домов на различных улицах
    };
    City Minsk;

private slots:
    void on_explicitInitializationButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    void ExplicitInitialization();
    void PrintCity(const City &city, QTextBrowser *textBrowser);
};
#endif // MAINWINDOW_H
