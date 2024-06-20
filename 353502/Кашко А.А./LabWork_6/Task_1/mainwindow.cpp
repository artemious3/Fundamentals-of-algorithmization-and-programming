#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char MainWindow::City::streets[5][25] = {
    "Nemiga",
    "Square of Victory",
    "Semashko",
    "Cherlenisa",
    "Zybitskaya"
};

int MainWindow::City::number_of_houses[5] = {70, 60, 65, 50, 55};

void MainWindow::ExplicitInitialization()
{
    Minsk = {1992862, 348.84, 'B', true};
}

void MainWindow::PrintCity(const City &city, QTextBrowser *textBrowser)
{
    QString output;
    output += "Population: " + QString::number(city.population) + " | ";
    output += "Area: " + QString::number(city.area) + " | ";
    output += "Country: " + QString(city.first_letter_country) + " | "; // Преобразуем city.country в QString
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

    textBrowser->append(output);
}

void MainWindow::on_explicitInitializationButton_clicked()
{
    ExplicitInitialization();
    PrintCity(Minsk, ui->textBrowser);
}

void MainWindow::on_pushButton_clicked()
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

    ui->textBrowser_2->append(output);
}

void MainWindow::on_pushButton_2_clicked()
{
    City city;
    City *cityPtr = &city;

    cityPtr->population = 1992862;
    cityPtr->area = 348.84;
    cityPtr->first_letter_country = 'B';
    cityPtr->capital = true;

    strncpy(cityPtr->streets[0], "Nemiga", sizeof(cityPtr->streets[0]) - 1);
    strncpy(cityPtr->streets[1], "Square of Victory", sizeof(cityPtr->streets[1]) - 1);
    strncpy(cityPtr->streets[2], "Semashko", sizeof(cityPtr->streets[2]) - 1);
    strncpy(cityPtr->streets[3], "Cherlenisa", sizeof(cityPtr->streets[3]) - 1);
    strncpy(cityPtr->streets[4], "Zybitskaya", sizeof(cityPtr->streets[4]) - 1);

    cityPtr->streets[0][sizeof(cityPtr->streets[0]) - 1] = '\0';
    cityPtr->streets[1][sizeof(cityPtr->streets[1]) - 1] = '\0';
    cityPtr->streets[2][sizeof(cityPtr->streets[2]) - 1] = '\0';
    cityPtr->streets[3][sizeof(cityPtr->streets[3]) - 1] = '\0';
    cityPtr->streets[4][sizeof(cityPtr->streets[4]) - 1] = '\0';

    cityPtr->number_of_houses[0] = 70;
    cityPtr->number_of_houses[1] = 60;
    cityPtr->number_of_houses[2] = 65;
    cityPtr->number_of_houses[3] = 50;
    cityPtr->number_of_houses[4] = 55;

    QString output;
    output += "Population: " + QString::number(cityPtr->population) + " | ";
    output += "Area: " + QString::number(cityPtr->area) + " | ";
    output += "Country: " + QString(cityPtr->first_letter_country) + " | "; // Преобразуем city.first_letter_country в QString
    output += "Capital: " + QString(cityPtr->capital ? "Yes" : "No") + " | ";

    output += "Streets: ";
    for (int i = 0; i < 5; ++i) {
        output += cityPtr->streets[i];
        if (i < 4) {
            output += " | ";
        }
    }
    output += " | Houses: ";
    for (int i = 0; i < 5; ++i) {
        output += QString::number(cityPtr->number_of_houses[i]);
        if (i < 4) {
            output += " | ";
        }
    }
    output += "\n";

    ui->textBrowser_3->append(output);
}

void MainWindow::on_pushButton_3_clicked()
{
    City Minsk;
    City &cityRef = Minsk;

    cityRef.population = 1992862;
    cityRef.area = 348.84;
    cityRef.first_letter_country = 'B';
    cityRef.capital = true;

    strncpy(cityRef.streets[0], "Nemiga", sizeof(cityRef.streets[0]) - 1);
    strncpy(cityRef.streets[1], "Square of Victory", sizeof(cityRef.streets[1]) - 1);
    strncpy(cityRef.streets[2], "Semashko", sizeof(cityRef.streets[2]) - 1);
    strncpy(cityRef.streets[3], "Cherlenisa", sizeof(cityRef.streets[3]) - 1);
    strncpy(cityRef.streets[4], "Zybitskaya", sizeof(cityRef.streets[4]) - 1);

    cityRef.streets[0][sizeof(cityRef.streets[0]) - 1] = '\0';
    cityRef.streets[1][sizeof(cityRef.streets[1]) - 1] = '\0';
    cityRef.streets[2][sizeof(cityRef.streets[2]) - 1] = '\0';
    cityRef.streets[3][sizeof(cityRef.streets[3]) - 1] = '\0';
    cityRef.streets[4][sizeof(cityRef.streets[4]) - 1] = '\0';

    cityRef.number_of_houses[0] = 70;
    cityRef.number_of_houses[1] = 60;
    cityRef.number_of_houses[2] = 65;
    cityRef.number_of_houses[3] = 50;
    cityRef.number_of_houses[4] = 55;

    QString output;
    output += "Population: " + QString::number(cityRef.population) + " | ";
    output += "Area: " + QString::number(cityRef.area) + " | ";
    output += "Country: " + QString(cityRef.first_letter_country) + " | "; // Преобразуем city.first_letter_country в QString
    output += "Capital: " + QString(cityRef.capital ? "Yes" : "No") + " | ";

    output += "Streets: ";
    for (int i = 0; i < 5; ++i) {
        output += cityRef.streets[i];
        if (i < 4) {
            output += ", ";
        }
    }
    output += " | Houses: ";
    for (int i = 0; i < 5; ++i) {
        output += QString::number(cityRef.number_of_houses[i]);
        if (i < 4) {
            output += ", ";
        }
    }
    output += "\n";

    ui->textBrowser_4->append(output);
}

