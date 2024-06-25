#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QPair>
#include <QString>
#include <QVector>
#include "primes.h"

class HashTable {
 public:
  QVector<int> table;
  int size;
  int counter = 0;

  HashTable(int s) : size(s) {

    table.resize(size);
    table.fill(-1);
  }

  virtual int hashFunc(int key) = 0;

  int secondHashFunc(int key) { return 1 + key % (size - 1); }

  int searchByKey(int key) {
    int index = hashFunc(key);
    int offset = secondHashFunc(key);

    if (table[index]== key) {
      return table[index];
    }

    while (!table[index] == -1) {
      index = (index + offset) % size;

      if (table[index] == key) {
        return table[index];
      }
    }

    return -1;
  }

  void insert(int key) {
      if(searchByKey(key) != -1){
          return;
      }
    ++counter;
    int index = hashFunc(key);
    int offset = secondHashFunc(key);

    if (table[index]== -1) {
      table[index] = key;
      return;
    }
    while (table[index]!=-1) {
      index = (index + offset) % size;
    }

   table[index] = key;
  }

  QVector<int> getTable() const { return table; }
};

#endif  // HASHTABLE_H
