#include "workmassfile.h"
#include "ui_workmassfile.h"

WorkMassFile::WorkMassFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkMassFile)
{
    ui->setupUi(this);

    ui->massButton->hide();
    ui->massLabel->hide();
    ui->massTextEdit->hide();
}

WorkMassFile::~WorkMassFile()
{
    delete ui;
}

void WorkMassFile::on_sizeMassButton_clicked()
{
    bool correctInput = false;
    QString size = ui->sizeMassTextEdit->toPlainText();
    sizeMass = ui->sizeMassTextEdit->toPlainText().toInt(&correctInput);
    if (correctInput) {
        ui->sizeInputLabel->clear();
        ui->sizeInputLabel->setText("Размер массива: " + size);

        ui->sizeMassButton->hide();
        ui->massButton->show();
        ui->massLabel->show();
        ui->massTextEdit->show();
    } else {
        ui->sizeInputLabel->setText("Некорректный ввод! Введите число!");
    }
}

void WorkMassFile::on_massButton_clicked()
{
    QString massInput = ui->massTextEdit->toPlainText();
    QStringList stringList = massInput.split(" ", Qt::SkipEmptyParts);
    int counterSize = 0;

    bool inputCorrect = true;
    for (const QString &str : stringList) {
        bool ok;
        str.toInt(&ok);
        if (!ok) {
            inputCorrect = false;
            break;
        } else {
            counterSize++;
        }
    }

    if (!inputCorrect) {
        ui->massInputLabel->setText("Некорректный ввод! Введите через пробел!");
        return;
    }
    else if (counterSize != sizeMass) {
        ui->massInputLabel->setText("Некорректный ввод! Неверное количество элементов!");
        return;
    }
    else {
        ui->massInputLabel->clear();
        ui->massInputLabel->setText("Массив записан в файл");

        QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьМассива.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QString formattedString = stringList.join("^");

            QTextStream out(&file);
            out << formattedString << "^"; // Добавляем '^' в конце
            file.close();
        }
    }
}

void WorkMassFile::on_showButton_clicked()
{
    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьМассива.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения";
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll(); // Считываем весь файл в строку
    file.close();

    QStringList elements = fileContent.split("^", Qt::SkipEmptyParts);
    QString output = elements.join(" ");
    ui->showTextBrowser->setPlainText(output);
}

