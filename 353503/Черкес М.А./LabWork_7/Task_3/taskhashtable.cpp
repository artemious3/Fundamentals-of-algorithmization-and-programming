#include "taskhashtable.h"

TaskHashTable::TaskHashTable(int size) : HashTable(size) {}

unsigned int TaskHashTable::generateRandomNumber() {
  return QRandomGenerator::global()->bounded(1000);
}

QString TaskHashTable::generateRandomString(unsigned int length) {
  QString randomString;
  static const char alphanum[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  for (unsigned int i = 0; i < length; ++i) {
    randomString += alphanum[QRandomGenerator::global()->bounded(
        static_cast<int>(sizeof(alphanum) - 1))];
  }

  return randomString;
}

void TaskHashTable::fillWithRandomData(int numEntries) {
  for (int i = 0; i < numEntries; ++i) {
    add(generateRandomNumber(), generateRandomString(10));
  }
}

void TaskHashTable::deleteEvenKeys() {
  for (int i = 0; i < tableSize; ++i) {
    Stack<Data>& stack = table[i];
    for (int j = 0; j < stack.getSize();) {
      if (stack.at(j).key % 2 == 0) {
        stack.pop();
      } else {
        ++j;
      }
    }
  }
}
