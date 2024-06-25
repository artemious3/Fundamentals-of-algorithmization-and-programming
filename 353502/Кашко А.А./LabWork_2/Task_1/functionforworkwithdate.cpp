#include "functionforworkwithdate.h"

FunctionForWorkWithDate::FunctionForWorkWithDate() {}

QDate FunctionForWorkWithDate::getNextDay(const QString &dateString)
{
    // Преобразование строки с датой в объект QDate
    QDate currentDate = QDate::fromString(dateString, "dd.MM.yyyy");
    int year = currentDate.year();

    if (isLeapYear(year) && currentDate.month() == 2 && currentDate.day() == 28) {
        return currentDate.addDays(2); // Переход с 28 февраля на 1 марта
    }

    return currentDate.addDays(1);
}

QDate FunctionForWorkWithDate::getPreviousDay(const QString &dateString)
{
    // Преобразование строки с датой в объект QDate
    QDate currentDate = QDate::fromString(dateString, "dd.MM.yyyy");

    // Получение следующей даты путем добавления одного дня к текущей дате
    return currentDate.addDays(-1);
}

void FunctionForWorkWithDate::writeToFile(const QString &filePath, const QString &dateString)
{
    QFile file(filePath);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly
                  | QIODevice::Text); // Создание нового файла, если файла не существует
    } else {
        file.open(QIODevice::Append | QIODevice::Text); // Добавление данных в существующий файл
    }

    QTextStream out(&file);
    out << dateString << "\n";

    file.close();
}

bool FunctionForWorkWithDate::isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int FunctionForWorkWithDate::getWeekNumber(const QString &dateString)
{
    QDate currentDate = QDate::fromString(dateString, "dd.MM.yyyy");
    return currentDate.weekNumber();
}

int FunctionForWorkWithDate::DaysDifference(int rowNumber, QDate selectedDate, QDate date)
{
    //считаем разницу между двумя датами
    int daysDifference = date.daysTo(selectedDate);
    if (daysDifference < 0) {
        daysDifference = -1 * daysDifference;
    }

    return daysDifference;
}
