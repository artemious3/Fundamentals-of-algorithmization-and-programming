#include <QThread>
#include "hashtable.h"

HashTable::HashTable(int V) {
    capacity = getNextPrime(V);
    table.resize(capacity);
    size = 0;
}

bool HashTable::isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int HashTable::getNextPrime(int n) {
    while (!isPrime(n))
        n++;
    return n;
}

int HashTable::hashFunction(int key) {
    return key % capacity;
}

void HashTable::insertItem(int key, int data) {

    if (loadFactor() >= 0.5) {
        expandTable();
    }

    int index = hashFunction(key);
    while (table[index].first != 0) {
        index = (index + 1) % capacity;
    }
    table[index] = qMakePair(key, data);
    size++;
}

void HashTable::deleteItem(int key) {
    size--;
    int index = hashFunction(key);
    while (table[index].first != key && table[index].first != 0) {
        index = (index + 1) % capacity;
    }
    if (table[index].first == key) {
        table[index] = qMakePair(0, 0);
    }
}


QVector<QPair<int, int>> HashTable::displayHash() {
    return table;
}

void HashTable::clear() {
    table.fill(qMakePair(0, 0));
}

int HashTable::findItem(int key) {
    int index = hashFunction(key);
    while (table[index].first != key && table[index].first != 0) {
        index = (index + 1) % capacity;
        QThread::msleep(1);
    }
    if (table[index].first == key) {
        return table[index].second;
    }
    return -1;
}

float HashTable::loadFactor() {
    return (float)size / (float)capacity;
}

void HashTable::expandTable() {
    int newCapacity = capacity * 2;
    QVector<QPair<int, int>> newTable(newCapacity);
    for (int i = 0; i < capacity; ++i) {
        if (table[i].first != 0) {
            int newIndex = table[i].first % newCapacity;
            while (newTable[newIndex].first != 0) {
                newIndex = (newIndex + 1) % newCapacity;
            }
            newTable[newIndex] = table[i];
        }
    }
    table = newTable;
    capacity = newCapacity;
}
