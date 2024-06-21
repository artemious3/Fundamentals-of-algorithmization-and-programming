#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QDebug>
#include <QStack>
#include <QVector>
#include <cmath>
#include "sizes.h"

static const double a = (sqrt(5) - 1) / 2;

class HashTable {
 public:
  explicit HashTable() {
    indexOfSize = 0;
    size = sizesOfTable[indexOfSize];
    table.resize(size);
  }

  int hashFunc(int key) { return int(double(key * a - int(key * a)) * size); }

  void insert(int key) {
      if(searchByKey(key) != -1){
          return;
      }
    int index = hashFunc(key);
    table[index].push(key);
    ++counter;
    if (double(counter) / size >= 0.75) {
      resize();
    }
  }

  int searchByKey(const int& key) {
    int index = hashFunc(key) % size;
    QStack<int> stack = table[index];

    while (!stack.empty()) {
      if (stack.top() == key) {
        return index;  // Возвращаем индекс стека в таблице
      }
      stack.pop();
    }
    return -1;
  }

  int removeByKey(const int& key) {
    int index = hashFunc(key) % size;
    QStack<int>& stack = table[index];
    QStack<int> tempStack;
    bool found = false;

    while (!stack.empty()) {
      if (stack.top() == key) {
        found = true;
      } else {
        tempStack.push(stack.top());
      }
      stack.pop();
    }

    while (!tempStack.empty()) {
      stack.push(tempStack.top());
      tempStack.pop();
    }

    return found ? key : -1;
  }

  QVector<int> getAllKeys() {
    QVector<int> keys;
    for (int i = 0; i < size; ++i) {
      QStack<int> temp = table[i];
      while (!temp.empty()) {
        keys.push_back(temp.top());
        temp.pop();
      }
    }
    return keys;
  }

  int countLargestKeys() {
    int count = 0, total = 0;
    QVector<int> keys = getAllKeys();
    for (auto key : keys) {
      total += hashFunc(key);
    }
    double average = double(total) / keys.size();
    for (auto key : keys) {
      if (hashFunc(key) > average) {
        ++count;
      }
    }
    return count;
  }

  QString printHashTable() {
    QString text = "";
    text += "\nHash Table:\n";
    for (int i = 0; i < size; ++i) {
      text += "Index " + QString::number(i) + ": ";
      QStack<int> temp = table[i];
      while (!temp.empty()) {
        text += QString::number(temp.top()) + " ";
        temp.pop();
      }
      text += '\n';
    }
    return text;
  }

  int getSize() const { return size; }

  QVector<QStack<int>> table;

  int getCounter() const { return counter; }

 private:
  int size;
  int counter{};
  int indexOfSize{};

  void resize() {
    ++indexOfSize;
    if (indexOfSize >= capacity) {
      return;
    }
    int newSize = sizesOfTable[indexOfSize];
    QVector<QStack<int>> newTable(newSize);

    // Перехеширование элементов в новую таблицу
    for (int i = 0; i < size; ++i) {
      while (!table[i].empty()) {
        int element = table[i].top();
        table[i].pop();
        int newIndex = int(double(element * a - int(element * a)) * newSize);
        newTable[newIndex].push(element);
      }
    }

    table = std::move(newTable);
    size = newSize;
  }
};
#endif  // HASHTABLE_H
