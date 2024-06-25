#include "workstructbinfile.h"
#include "ui_workstructbinfile.h"

WorkStructBinFile::WorkStructBinFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkStructBinFile)
{
    ui->setupUi(this);
}

WorkStructBinFile::~WorkStructBinFile()
{
    delete ui;
}

void WorkStructBinFile::on_inputFileButton_clicked()
{
    QString populationText = ui->textEdit_7->toPlainText();
    QString areaText = ui->textEdit_8->toPlainText();
    QString countryText = ui->textEdit_9->toPlainText();
    QString capitalText = ui->textEdit_10->toPlainText();
    QString streetsText = ui->textEdit_11->toPlainText();
    QString housesText = ui->textEdit_12->toPlainText();

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

    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьСтруктурыБин.txt");
    if (!file.open(QIODevice::Append)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QDataStream out(&file);
    out.writeRawData(reinterpret_cast<const char*>(&city), sizeof(city));

    file.close();
}

void WorkStructBinFile::on_pushButton_2_clicked()
{
    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьСтруктурыБин.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }

    QDataStream in(&file);

    while (!in.atEnd()) {
        City city;

        in.readRawData(reinterpret_cast<char*>(&city), sizeof(city));

        QString output = "Population: " + QString::number(city.population) + "; ";
        output += "Area: " + QString::number(city.area) + " ; ";
        output += "Country: " + QString(city.first_letter_country) + "; ";
        output += "Capital: " + QString(city.capital ? "Yes" : "No") + "; ";
        output += "Streets: ";
        for (int i = 0; i < 5; ++i) {
            output += QString(city.streets[i]) + "; ";
        }
        output += "Houses: ";
        for (int i = 0; i < 5; ++i) {
            output += QString::number(city.number_of_houses[i]) + "; ";
        }

        ui->textBrowser->append(output);
    }

    file.close();
}


