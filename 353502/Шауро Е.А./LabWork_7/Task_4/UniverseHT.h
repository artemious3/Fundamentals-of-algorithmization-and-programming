#ifndef UNIVERSEHT_H
#define UNIVERSEHT_H
#include <QRandomGenerator>
#include <QDebug>
#include "hashtable.h"

class UniverseHT : public HashTable {
 public:
  explicit UniverseHT(int s) : size(s), HashTable(s) {
        qDebug() << "size into class" << size;
    QRandomGenerator::securelySeeded();
    a = QRandomGenerator::global()->bounded(1, size);
    b = QRandomGenerator::global()->bounded(size);
    p = convertToIndex(size);
  }

  int hashFunc(int key) override { return ((a * key + b) % p) % size; }

 private:
  int convertToIndex(int number) {

    if (number == 16) {
      primeIndex = 0;
    } else if (number == 64) {
      primeIndex = 1;
    } else if (number == 128) {
      primeIndex = 2;
    } else if (number == 2048) {
      primeIndex = 3;
    } else {
      return -1;
    }
    return primes[primeIndex];
  }

  int a, b, p, size, primeIndex;

};

#endif  // UNIVERSEHT_H
