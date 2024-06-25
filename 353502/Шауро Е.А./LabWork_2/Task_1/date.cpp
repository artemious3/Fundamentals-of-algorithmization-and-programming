#include "date.h"

Date::Date() {
  curDate = QDate::currentDate();
}

QDate Date::NextDay(const QDate& date) {
  return date.addDays(1);
}

QDate Date::PreviosDay(const QDate& date) {
  return date.addDays(-1);
}

bool Date::IsLeap(const int year) {
  return (year % 4 == 0) &&
         ((year % HUNDREED != 0) || (year % (HUNDREED * 4) == 0));
}

int16_t Date::WeekNumber(const QDate& date) {
  QDate firstDayOfTheYear(date.year(), 1, 1);
  int64_t distance = firstDayOfTheYear.daysTo(date);

  return int16_t(distance / DAYSATWEEK) + 1;
}

int Date::DaysTillMyBirthday(const QDate& birthdaydate, const QDate& date) {
  QDate helperDate(date.year(), birthdaydate.month(), birthdaydate.day()),
      twentyNine(birthdaydate.year(), 02, LASTFEB);
  Date someDate;
  int days, year;

  if (birthdaydate.month() == 2 && birthdaydate.day() == LASTLEAPFEB) {
    if (std::abs(birthdaydate.year() - date.year()) >= 4) {

      year = birthdaydate.year() > date.year()
                 ? birthdaydate.year() - 4 + date.year() % 4
                 : birthdaydate.year() - date.year() % 4;

      helperDate.setDate(year, date.month(), date.day());

      days = someDate.Duration(helperDate, birthdaydate);
    }

    else {
      days = date.daysTo(twentyNine) + 1;
      days = days < 0 ? date.daysInYear() * 4 + days : days;
    }
  }

  else {
    days = date.daysTo(helperDate);
    days = days < 0 ? date.daysInYear() + days : days;
  }

  return days;
}

int Date::Duration(const QDate& firsDate, const QDate& secondDate) {
  int days = 0;
  QDate thBiggestDate = firsDate > secondDate ? firsDate : secondDate;
  QDate theSmallestDate = firsDate < secondDate ? firsDate : secondDate;

  while (theSmallestDate < thBiggestDate) {
    theSmallestDate = theSmallestDate.addDays(1);
    days++;
  }
  return days;
}

QDate Date::getCurDate() {
  return curDate;
}
