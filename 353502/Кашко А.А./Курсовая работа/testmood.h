#ifndef TESTMOOD_H
#define TESTMOOD_H

#include <QDialog>
#include <QList>
#include <QRadioButton>

#include "puzzlethemes.h"

namespace Ui {
class TestMood;
}

class TestMood : public QDialog
{
    Q_OBJECT

public:
    explicit TestMood(QWidget *parent = nullptr);
    ~TestMood();

private slots:
    void on_buttonNextQuestion_1_clicked();

    void on_buttonNextQuestion_2_clicked();

    void on_buttonNextQuestion_3_clicked();

    void on_buttonNextQuestion_4_clicked();

    void on_buttonNextQuestion_5_clicked();

    void on_button_checkingResults_clicked();

    void on_buttonStartPuzzle_clicked();

    void on_buttonNextQuestion_6_clicked();

    void on_buttonNextQuestion_7_clicked();

    void on_buttonNextQuestion_8_clicked();

    void on_buttonNextQuestion_9_clicked();

    void on_buttonNextQuestion_10_clicked();

private:
    Ui::TestMood *ui;

    // счётчики для определения настроения
    int counterGood = 0;
    int counterNormal = 0;
    int counterIrritated = 0;   // раздражённый
    int counterWicked = 0;      // злой
    int counterSad = 0;
    bool check;
    int userSelection;

    QList<QRadioButton*> radioButtons;

    void CounterMood();
    void CheckingAnswerOfTest();
    void results_ofTest(int mood1, int mood2, int mood3, int mood4, int mood5);
};

#endif // TESTMOOD_H
