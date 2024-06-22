#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QStack>

template <typename T>
class Item {
public:
    int key;
    T value;

    Item() : key(0), value(T()) {}
    Item(int key, T value);
};


template <typename T>
class HashTable {
public:
    HashTable(int size);
    ~HashTable();

    void insert(int key, T value);
    T get(int key);
    void remove(int key);
    Item<T> findMaxKeyItem() const;

protected:
    QStack<Item<T>>* table;
    int size;

    int hashFunction(int key) const;
};


#endif // HASHTABLE_H
