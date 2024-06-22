#ifndef DATE_H
#define DATE_H
#include <QDate>
#include <QDebug>
#include <cmath>
#include "const.h"

class Date {
private:
    QDate curDate;

public:
    Date();
    QDate NextDay(const QDate& date);
    QDate PreviosDay(const QDate& date);
    bool IsLeap(const int year);
    int16_t WeekNumber(const QDate& date);
    int DaysTillMyBirthday(const QDate& birthdaydate, const QDate& date);
    int Duration(const QDate& firsDate, const QDate& secondDate);
    QDate getCurDate();
};

#endif  // DATE_H
