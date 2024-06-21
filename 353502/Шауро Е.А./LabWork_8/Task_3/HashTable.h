#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QDebug>
#include <QPair>
#include <QVector>
#include <cmath>
#include "sizes.h"

static const double a = (sqrt(5) - 1) / 2;

template <typename Key, typename Value>
class HashTable {
  std::hash<Key> hasher;

 public:
  struct Pair {
    Key key;
    Value value;
    bool isDeleted;

    Pair(Key k = Key(), Value v = Value(), bool deleted = false)
        : key(k), value(v), isDeleted(deleted) {}
  };

  explicit HashTable() {
    indexOfSize = 0;
    size = sizesOfTable[indexOfSize];
    table = QVector<Pair>(size, Pair{-1, Value{}, true});
  }

  int hashFunc(Key key) const {
    return int(double(hasher(key) * a - int(hasher(key) * a)) * size);
  }

  int secondHashFunc(Key key) const { return 1 + hasher(key) % (size - 1); }

  void insert(Pair pair) {
    Key key = pair.key;
    int index = hashFunc(key);
    int offset = secondHashFunc(key);

    while (!table[index].isDeleted && table[index].key != key &&
           table[index].key != -1) {
      index = (index + offset) % size;
    }

    if (table[index].isDeleted || table[index].key == -1) {
      table[index] = pair;
      ++counter;

      if (counter >= size * loadFactor) {
        resize();
      }
    }
  }

  const Value& operator[](const Key& key) const {
    if (key > capacity) {
      throw std::out_of_range("Key not found in hash table");
    }
    return table[key].value;
  }

  Value& operator[](const Key& key) {
    if (key > capacity) {
      throw std::out_of_range("Key not found in hash table");
    }
    return table[key].value;
  }

  int searchByKey(const Key& key) const {
    int index = hashFunc(hasher(key));
    int offset = secondHashFunc(hasher(key));
    int originalIndex = index;

    while (!table[index].isDeleted && table[index].key != key &&
           table[index].key != -1) {
      index = (index + offset) % size;

      // Если произошло зацикливание, то прекращаем поиск
      if (index == originalIndex) {
        return -1;  // Возвращаем -1, если элемент не найден
      }
    }

    if (table[index].key == key && !table[index].isDeleted) {
      return index;
    }

    return -1;  // Возвращаем -1, если элемент не найден
  }

  bool contains(Key key) const { return searchByKey(key) != -1; }

  void clear() {
    for (auto& pair : table) {
      pair = Pair{-1, Value{}, true};
    }
  }

  int removeByKey(const Key& key) {
    int index = searchByKey(key);

    if (index != -1) {
      table[index].isDeleted = true;
      --counter;
      return index;
    }

    return -1;  // Элемент не найден или уже удален
  }

  int getSize() const { return size; }

  int getCounter() const { return counter; }

 private:
  int size;
  int counter = 0;
  int indexOfSize = 0;
  const double loadFactor = 0.75;  // Фактор загрузки для решения коллизий

  QVector<Pair> table;

  void resize() {
    ++indexOfSize;
    if (indexOfSize >= capacity) {
      return;
    }

    int newSize = sizesOfTable[indexOfSize];
    QVector<Pair> newTable(newSize, Pair{-1, Value{}, true});

    // Перехеширование элементов в новую таблицу
    for (const auto& pair : table) {
      if (!pair.isDeleted && pair.key != -1) {
        int newIndex = hashFunc(pair.key);
        int newOffset = secondHashFunc(pair.key);

        while (!newTable[newIndex].isDeleted &&
               newTable[newIndex].key != pair.key &&
               newTable[newIndex].key != -1) {
          newIndex = (newIndex + newOffset) % newSize;
        }

        if (newTable[newIndex].isDeleted || newTable[newIndex].key == -1) {
          newTable[newIndex] = pair;
        }
      }
    }

    table = std::move(newTable);
    size = newSize;
  }
};

#endif  // HASHTABLE_H
