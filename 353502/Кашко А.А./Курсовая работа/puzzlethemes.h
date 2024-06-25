#ifndef PUZZLETHEMES_H
#define PUZZLETHEMES_H

#include <QDialog>
#include <QPalette>

#include "helppuzzle.h"
#include "averagepuzzles.h"
#include "hardpuzzles.h"
#include "puzzletime.h"

namespace Ui {
class PuzzleThemes;
}

class PuzzleThemes : public QDialog
{
    Q_OBJECT

public:
    explicit PuzzleThemes(QWidget *parent = nullptr);
    ~PuzzleThemes();

public:
    void deleteThemes(int userSelection);

private slots:
    void on_button_StartGame_clicked();

private:
    Ui::PuzzleThemes *ui;

    int selectionLevel_1, selectionLevel_2;
};

#endif // PUZZLETHEMES_H
