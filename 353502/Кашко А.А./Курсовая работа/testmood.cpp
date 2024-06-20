#include "testmood.h"
#include "ui_testmood.h"

TestMood::TestMood(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TestMood)
{
    ui->setupUi(this);

    ui->buttonNextQuestion_2->hide();
    ui->buttonNextQuestion_2->setStyleSheet("background-color: orange;");

    ui->buttonNextQuestion_3->hide();
    ui->buttonNextQuestion_3->setStyleSheet("background-color: yellow;");

    ui->buttonNextQuestion_4->hide();
    ui->buttonNextQuestion_4->setStyleSheet("background-color: blue;");

    ui->buttonNextQuestion_5->hide();
    ui->buttonNextQuestion_5->setStyleSheet("background-color: green;");

    ui->buttonNextQuestion_6->hide();
    ui->buttonNextQuestion_6->setStyleSheet("background-color: purple;");

    ui->buttonNextQuestion_7->hide();
    ui->buttonNextQuestion_7->setStyleSheet("background-color: pink;");

    ui->buttonNextQuestion_8->hide();
    ui->buttonNextQuestion_8->setStyleSheet("background-color: red;");

    ui->buttonNextQuestion_9->hide();
    ui->buttonNextQuestion_9->setStyleSheet("background-color: orange;");

    ui->buttonNextQuestion_10->hide();
    ui->buttonNextQuestion_10->setStyleSheet("background-color: yellow;");

    ui->buttonNextQuestion_1->setStyleSheet("background-color: red;");
    ui->button_checkingResults->hide();
    ui->buttonStartPuzzle->hide();
    ui->ShowAnswerEdit->hide();

    QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/morning.jpg"); // путь к изображению
    ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

    radioButtons = {ui->AnswerNumber_1, ui->AnswerNumber_2, ui->AnswerNumber_3, ui->AnswerNumber_4, ui->AnswerNumber_5};
}

TestMood::~TestMood()
{
    delete ui;
}

void TestMood::on_buttonNextQuestion_1_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/vegetables.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("С каким овощем ты можешь себя сравнить?");
        ui->buttonNextQuestion_1->hide();

        ui->buttonNextQuestion_2->show();
        ui->AnswerNumber_1->setText("Счастливый и свежий огурец");
        ui->AnswerNumber_2->setText("Обычная редиска");
        ui->AnswerNumber_3->setText("Измученный картофель");
        ui->AnswerNumber_4->setText("Злой помидор");
        ui->AnswerNumber_5->setText("Раздавленный горох");
    }
}

void TestMood::on_buttonNextQuestion_2_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/superplay.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Если бы вы были супергероем, то какую способность бы хотели иметь?");
        ui->buttonNextQuestion_2->hide();

        ui->buttonNextQuestion_3->show();
        ui->AnswerNumber_1->setText("Летать в облаках из сахарной ваты");
        ui->AnswerNumber_2->setText("Мне и человеком быть нормально");
        ui->AnswerNumber_3->setText("Читать мысли людей");
        ui->AnswerNumber_4->setText("Управлять действиями людей");
        ui->AnswerNumber_5->setText("Какой из меня супергерой");
    }
}

void TestMood::on_buttonNextQuestion_3_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/music.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Какую бы песню вы сейчас послушали?");
        ui->buttonNextQuestion_3->hide();

        ui->buttonNextQuestion_4->show();
        ui->AnswerNumber_1->setText("О весёлых пиявках в пруду");
        ui->AnswerNumber_2->setText("О колючем и спокойном ёжике");
        ui->AnswerNumber_3->setText("О разъярённой пчеле");
        ui->AnswerNumber_4->setText("О зубастом крокодиле");
        ui->AnswerNumber_5->setText("О долгожительнице-черепахе");
    }
}

void TestMood::on_buttonNextQuestion_4_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/animal.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Что бы вы спросили у животных?");
        ui->buttonNextQuestion_4->hide();

        ui->buttonNextQuestion_5->show();
        ui->AnswerNumber_1->setText("Почему они такие милые?");
        ui->AnswerNumber_2->setText("Зачем у них что-то спрашивать?");
        ui->AnswerNumber_3->setText("Почему у них так мало проблем?");
        ui->AnswerNumber_4->setText("Почему большинство из них вечно злые на людей?");
        ui->AnswerNumber_5->setText("Почему мы не понимаем их языка?");
    }
}

void TestMood::on_buttonNextQuestion_5_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/emoutions.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Какая вы эмоция?");
        ui->buttonNextQuestion_5->hide();

        ui->buttonNextQuestion_6->show();
        ui->AnswerNumber_1->setText("Радость");
        ui->AnswerNumber_2->setText("Безразличие");
        ui->AnswerNumber_3->setText("Раздражённость");
        ui->AnswerNumber_4->setText("Злость");
        ui->AnswerNumber_5->setText("Грусть");
    }
}

void TestMood::on_buttonNextQuestion_6_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/flower.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("С каким цветком вы бы себя сравнили?");
        ui->buttonNextQuestion_6->hide();

        ui->buttonNextQuestion_7->show();
        ui->AnswerNumber_1->setText("Красивый нежный тюльпан");
        ui->AnswerNumber_2->setText("Обычная ромашка");
        ui->AnswerNumber_3->setText("Мухоловка");
        ui->AnswerNumber_4->setText("Колючая роза");
        ui->AnswerNumber_5->setText("Раздавленный клевер");
    }
}


void TestMood::on_buttonNextQuestion_7_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/body.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("С какой частью тела вы бы себя сравнили?");
        ui->buttonNextQuestion_7->hide();

        ui->buttonNextQuestion_8->show();
        ui->AnswerNumber_1->setText("Стройная талия");
        ui->AnswerNumber_2->setText("Самый обычный палец");
        ui->AnswerNumber_3->setText("Длинный нос");
        ui->AnswerNumber_4->setText("Большой и широкий рот");
        ui->AnswerNumber_5->setText("Плачущие глаза");
    }
}


void TestMood::on_buttonNextQuestion_8_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/eat.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Кто вы из еды?");
        ui->buttonNextQuestion_8->hide();

        ui->buttonNextQuestion_9->show();
        ui->AnswerNumber_1->setText("Вкусная сочная пицца");
        ui->AnswerNumber_2->setText("Полезный суп");
        ui->AnswerNumber_3->setText("Невкусная печёнка");
        ui->AnswerNumber_4->setText("Рыба с косточками");
        ui->AnswerNumber_5->setText("Протухшая котлета");
    }
}


void TestMood::on_buttonNextQuestion_9_clicked()
{
    CheckingAnswerOfTest();

    if (check)
    {
        QPixmap backgroundImage("/home/nastya/coursework_puzzles/image/present.jpg"); // путь к изображению
        ui->PictureForTest->setPixmap(backgroundImage.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

        CounterMood();

        ui->TestQuestion->setText("Какой вы подарок?");
        ui->buttonNextQuestion_9->hide();

        ui->buttonNextQuestion_10->show();
        ui->AnswerNumber_1->setText("Большой и красивый подарок");
        ui->AnswerNumber_2->setText("Самый простой и стандартный подарок");
        ui->AnswerNumber_3->setText("Подарок, который не понравился получателю");
        ui->AnswerNumber_4->setText("Испорченный подарок");
        ui->AnswerNumber_5->setText("Маленький подарок");
    }
}

void TestMood::on_button_checkingResults_clicked()
{
    ui->buttonStartPuzzle->show();
    results_ofTest(counterGood, counterNormal, counterIrritated, counterWicked, counterSad);
}

void TestMood::on_buttonStartPuzzle_clicked()
{
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->deleteThemes(userSelection);
    puzzleThemes->show();
    this->hide();
}

void TestMood::on_buttonNextQuestion_10_clicked()
{
    ui->buttonNextQuestion_10->hide();
    ui->button_checkingResults->show();
    ui->ShowAnswerEdit->show();
    QPixmap backgroundImage_1("/home/nastya/coursework_puzzles/image/intresting.jpg"); // путь к изображению
    ui->PictureForTest->setPixmap(backgroundImage_1.scaled(ui->PictureForTest->size(), Qt::IgnoreAspectRatio));

    ui->TestQuestion->hide();
    ui->AnswerNumber_1->hide();
    ui->AnswerNumber_2->hide();
    ui->AnswerNumber_3->hide();
    ui->AnswerNumber_4->hide();
    ui->AnswerNumber_5->hide();
}

void TestMood::CheckingAnswerOfTest()
{
    bool checkIn = false;
    for(auto button : radioButtons)
    {
        if(button->isChecked())
        {
            checkIn = true;
        }
    }

    check = checkIn;
}

void TestMood::CounterMood()
{
    int countHelp = 0;
    for(auto button : radioButtons)
    {
        if(button->isChecked() && countHelp == 0) counterGood++;

        if(button->isChecked() && countHelp == 1) counterNormal++;

        if(button->isChecked() && countHelp == 2) counterIrritated++;

        if(button->isChecked() && countHelp == 3) counterWicked++;

        if(button->isChecked() && countHelp == 4) counterSad++;

        countHelp++;
    }
}

void TestMood::results_ofTest(int counterGood, int counterNormal, int counterIrritated, int counterWicked, int counterSad)
{
    QList<int> massMood = {counterGood, counterNormal, counterIrritated, counterWicked, counterSad};
    int max = counterGood;

    for(int i = 0; i < massMood.size(); i++)
    {
        if (massMood[i] > max) max = massMood[i];
    }

    if (max == counterGood)
    {
        ui->ShowAnswerEdit->setText("У вас хорошее настроение");
        userSelection = 0;
    }

    else if (max == counterNormal)
    {
        ui->ShowAnswerEdit->setText("У вас нормальное настроение");
        userSelection = 1;
    }

    else if (max == counterIrritated)
    {
        ui->ShowAnswerEdit->setText("Вы раздражены");
        userSelection = 2;
    }

    else if (max == counterWicked)
    {
        ui->ShowAnswerEdit->setText("Вы злы");
        userSelection = 3;
    }

    else
    {
        ui->ShowAnswerEdit->setText("У вас плохое настроение");
        userSelection = 4;
    }
}
