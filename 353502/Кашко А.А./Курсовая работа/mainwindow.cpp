#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->comboBox->hide();
    ui->pushButton_2->hide();
    ui->pushButton_4->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();

    ui->comboBox->setStyleSheet("background-color: blue;");
    ui->pushButton->setStyleSheet("background-color: green;");
    ui->pushButton_2->setStyleSheet("background-color: green;");
    ui->pushButton_7->setStyleSheet("background-color: blue;");
    ui->pushButton_8->setStyleSheet("background-color: green;");
    ui->pushButton_10->setStyleSheet("background-color: blue;");
    ui->pushButton_4->setStyleSheet("background-color: green;");

    QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/puz.jpg"); // путь к изображению
    ui->label->setPixmap(backgroundImage.scaled(ui->label->size(), Qt::IgnoreAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->comboBox->show();
    ui->pushButton_2->show();
    ui->pushButton_4->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton->hide();

}


void MainWindow::on_pushButton_7_clicked()
{
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->comboBox->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();

    TestMood *testMood = new TestMood();
    testMood->show();
    this->hide();
}

void MainWindow::on_pushButton_10_clicked()
{
    close();
}


void MainWindow::on_pushButton_8_clicked()
{
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->show();
    this->hide();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label_5->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    userSelection = ui->comboBox->currentIndex();
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->deleteThemes(userSelection);
    puzzleThemes->show();
    this->hide();
}

