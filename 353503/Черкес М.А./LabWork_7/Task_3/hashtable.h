#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QPair>
#include <QString>
#include <QVector>
#include "stack.h"

struct Data {
  int key;
  QString value;
};

class HashTable {
 protected:
  int tableSize;
  QVector<Stack<Data>> table;
  int filledSlots;

 public:
  int hashFunction(int key);

  HashTable(int size);

  void add(int key, const QString& value);

  void checkLoadFactor();

  void resize();

  QString find(int key);

  QVector<QVector<QPair<int, QString>>> displayHash();

  void remove(int key);

  void clear();

  int getTableSize();
};

#endif  // HASHTABLE_H
