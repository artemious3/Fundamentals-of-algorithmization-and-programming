#ifndef MATHERIC_H
#define MATHERIC_H
#include <QString>

struct Matheric {
  int peoples;
  double perimeter;
  char size;
  bool isSeasOpen;
  static constexpr char nationalities[] = {'E', 'R', 'U', 'B', 'T'};
  static constexpr int Temperatures[] = {-1, 0, 1, 2, 3, 4,
                                  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  static QString getTemperaturesString() {
    QString TemperaturesStr;
    for (int Temperature : Temperatures) {
      TemperaturesStr += QString::number(Temperature);
      TemperaturesStr += " ";
    }
    return TemperaturesStr.trimmed();
  }

  static QString getNationsString() {
    QString nationStr;
    for (char nation : nationalities) {
      nationStr += nation;
      nationStr += " ";
    }
    return nationStr.trimmed();
  }
};

#endif  // MATHERIC_H
