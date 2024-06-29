#ifndef TASKHASHTABLE_H
#define TASKHASHTABLE_H

#include <QRandomGenerator>
#include "hashtable.h"

class TaskHashTable : public HashTable {

 public:
  TaskHashTable(int size);

  unsigned int generateRandomNumber();

  QString generateRandomString(unsigned int length);

  void fillWithRandomData(int numEntries);

  void deleteEvenKeys();
};

#endif  // TASKHASHTABLE_H
