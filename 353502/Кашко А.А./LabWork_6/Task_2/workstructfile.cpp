#include "workstructfile.h"
#include "ui_workstructfile.h"

WorkStructFile::WorkStructFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkStructFile)
{
    ui->setupUi(this);
}

WorkStructFile::~WorkStructFile()
{
    delete ui;
}

void WorkStructFile::on_inputFileButton_clicked()
{
    QString populationText = ui->textEdit->toPlainText();
    QString areaText = ui->textEdit_2->toPlainText();
    QString countryText = ui->textEdit_3->toPlainText();
    QString capitalText = ui->textEdit_4->toPlainText();
    QString streetsText = ui->textEdit_5->toPlainText();
    QString housesText = ui->textEdit_6->toPlainText();

    if (populationText.isEmpty() || areaText.isEmpty() || countryText.isEmpty() ||
        capitalText.isEmpty() || streetsText.isEmpty() || housesText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    QStringList streetsList = streetsText.split(" ");

    if (streetsList.size() != 5) {
        QMessageBox::warning(this, "Ошибка", "Введите пять улиц через пробел!");
        return;
    }

    QStringList housesList = housesText.split(" ");

    if (housesList.size() != 5) {
        QMessageBox::warning(this, "Ошибка", "Введите пять номеров домов через пробел!");
        return;
    }

    bool ok;
    int population = populationText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод!");
        return;
    }

    double area = areaText.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод!");
        return;
    }

    char country = countryText.at(0).toLatin1(); // Получаем первый символ страны

    bool capital = false;
    QString capitalLower = capitalText.toLower();
    if (capitalLower == "yes") {
        capital = true;
    } else if (capitalLower != "no") {
        QMessageBox::warning(this, "Ошибка", "Некорректный ввод!");
        return;
    }

    City city;
    city.population = population;
    city.area = area;
    city.first_letter_country = country;
    city.capital = capital;

    for (int i = 0; i < 5; ++i) {
        strncpy(city.streets[i], streetsList.value(i).toUtf8().constData(), sizeof(city.streets[i]) - 1);
        city.streets[i][sizeof(city.streets[i]) - 1] = '\0'; // Убедимся, что строка заканчивается нулевым символом
    }

    for (int i = 0; i < 5; ++i) {
        city.number_of_houses[i] = housesList.value(i).toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Некорректный ввод!");
            return;
        }
    }

    QString output;
    output += "Population: " + QString::number(city.population) + " | ";
    output += "Area: " + QString::number(city.area) + " | ";
    output += "Country: " + QString(city.first_letter_country) + " | "; // Преобразуем city.first_letter_country в QString
    output += "Capital: " + QString(city.capital ? "Yes" : "No") + " | ";

    output += "Streets: ";
    for (int i = 0; i < 5; ++i) {
        output += city.streets[i];
        if (i < 4) {
            output += ", ";
        }
    }
    output += " | Houses: ";
    for (int i = 0; i < 5; ++i) {
        output += QString::number(city.number_of_houses[i]);
        if (i < 4) {
            output += ", ";
        }
    }
    output += "\n";

    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьСтруктуры.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    out << output;
    file.close();
}

void WorkStructFile::on_pushButton_2_clicked()
{
    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьСтруктуры.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    ui->textBrowser->setText(fileContent);
}

