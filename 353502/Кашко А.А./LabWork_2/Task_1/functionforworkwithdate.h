#ifndef FUNCTIONFORWORKWITHDATE_H
#define FUNCTIONFORWORKWITHDATE_H

#include <QDate>
#include <QFile>

class FunctionForWorkWithDate : public QObject
{
    Q_OBJECT
public:
    FunctionForWorkWithDate();

    QDate getNextDay(const QString &dateString);
    QDate getPreviousDay(const QString &dateString);

    bool isLeapYear(int year);

    int getWeekNumber(const QString &dateString);
    int DaysDifference(int rowCount, QDate dateTable, QDate date);

    void writeToFile(const QString &filePath, const QString &dateString);
};

#endif // FUNCTIONFORWORKWITHDATE_H
