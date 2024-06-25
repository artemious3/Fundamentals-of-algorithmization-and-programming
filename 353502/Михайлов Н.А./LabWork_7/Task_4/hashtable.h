#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "qlistwidget.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdexcept>

#include <climits>


template <typename T>
struct Item {
    std::string key;
    T value;
    bool isOccupied;

    Item() : key(""), value(T()), isOccupied(false) {}
    Item(const std::string& k, T v) : key(k), value(v), isOccupied(true) {}

    ~Item()
    {
    }
};

template <typename T>
class HashTable {
private:
    std::vector<Item<T>> table;
    int size;
    int p; // Простое число
    int a, b; // Случайные параметры для хеш-функции

    int hashFunction(const std::string &key);
    void resize();

public:
    HashTable(int size, int prime);
    ~HashTable();

    void insert(const std::string &key, T value);
    T search(const std::string &key);
    void remove(const std::string &key);

    void print(QListWidget* listWidget);
    void clear();
};

#endif // HASHTABLE_H
