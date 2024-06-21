#include <QDebug>
#include <QString>
#include <cmath>
#include <iostream>

void DecimalToBinary(int64_t number, QString* binaryStr) {
  if (number == 0) {
    *binaryStr = "0";
    return;
  }
  if (number == 1) {
    *binaryStr = "1";
    return;
  }

  int bit = number % 2;
  DecimalToBinary(number / 2, binaryStr);
  *binaryStr += QString::number(bit);
}

void AddFractionalPart(long double fractionalPart, QString* binaryStr,
                       int index) {
  if (index == 0) {
    return;
  }

  fractionalPart *= 2;
  *binaryStr += QString::number(int(fractionalPart));
  AddFractionalPart(fractionalPart - int(fractionalPart), binaryStr, index - 1);
}

int main() {
  qreal x = 14.59;
  int64_t xInt = int64_t(x);
  QString binaryStr;
  DecimalToBinary(std::abs(xInt), &binaryStr);

  if (x - xInt != 0) {
    binaryStr += '.';
    long double fractionalPart = std::abs(x - xInt);
    AddFractionalPart(fractionalPart, &binaryStr, 4);
  }

  std::cout << "Binary representation of " << x
            << " is: " << binaryStr.toStdString() << '\n';

  return 0;
}
