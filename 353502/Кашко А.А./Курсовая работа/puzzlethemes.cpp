#include "puzzlethemes.h"
#include "ui_puzzlethemes.h"

PuzzleThemes::PuzzleThemes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PuzzleThemes)
{
    ui->setupUi(this);
}

PuzzleThemes::~PuzzleThemes()
{
    delete ui;
}

void PuzzleThemes::deleteThemes(int userSelection)
{
    switch(userSelection) {
    case 0:
        ui->radiobutton_ThemesSeaOcean->hide();
        ui->radiobutton_ThemesAnimal->hide();
        ui->radiobutton_ThemesNature->hide();
        break;
    case 1:
        ui->radiobutton_ThemesSeaOcean->hide();
        ui->radiobutton_ThemesPlay->hide();
        break;
    case 2:
        ui->radiobutton_ThemesGoodmood->hide();
        ui->radiobutton_ThemesPlay->hide();
        break;
    case 3:
        ui->radiobutton_ThemesAnimal->hide();
        ui->radiobutton_ThemesPlay->hide();
        break;
    case 4:
        ui->radiobutton_ThemesAnimal->hide();
        ui->radiobutton_ThemesNature->hide();
        ui->radiobutton_ThemesSeaOcean->hide();
        break;
    default:
        break;
    }
}

void PuzzleThemes::on_button_StartGame_clicked()
{
    // выбор уровня сложности
    selectionLevel_1 = ui->comboBox->currentIndex();

    // выбор темы пазлов
    if (ui->radiobutton_ThemesSeaOcean->isChecked() && ui->radiobutton_ThemesSeaOcean->isVisible())
    {
        selectionLevel_2 = 0;
    }
    else if (ui->radiobutton_ThemesAnimal->isChecked() && ui->radiobutton_ThemesAnimal->isVisible())
    {
        selectionLevel_2 = 1;
    }
    else if (ui->radiobutton_ThemesNature->isChecked() && ui->radiobutton_ThemesNature->isVisible())
    {
        selectionLevel_2 = 2;
    }
    else if (ui->radiobutton_ThemesPlay->isChecked() && ui->radiobutton_ThemesPlay->isVisible())
    {
        selectionLevel_2 = 3;
    }
    else if (ui->radiobutton_ThemesGoodmood->isChecked() && ui->radiobutton_ThemesGoodmood->isVisible())
    {
        selectionLevel_2 = 4;
    }

    if (selectionLevel_1 == 0)
    {
        HelpPuzzle *puzzle = new HelpPuzzle();
        puzzle->themesPuzzle(selectionLevel_2);
        puzzle->show();
        this->hide();
    }

    else if (selectionLevel_1 == 1)
    {
        AveragePuzzles *puzzle_1 = new AveragePuzzles();
        puzzle_1->themesPuzzle(selectionLevel_2);
        puzzle_1->show();
        this->hide();
    }

    else if (selectionLevel_1 == 2)
    {
        HardPuzzles *puzzle_2 = new HardPuzzles();
        puzzle_2->themesPuzzle(selectionLevel_2);
        puzzle_2->show();
        this->hide();
    }

    else if (selectionLevel_1 == 3)
    {
        PuzzleTime *puzzle_2 = new PuzzleTime();
        puzzle_2->show();
        this->hide();
    }
}

