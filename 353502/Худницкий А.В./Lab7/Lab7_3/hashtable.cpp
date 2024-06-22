#include "hashtable.h"
#include <cstddef>
#include <math.h>

template<typename T>
Item<T>::Item(int key, T value) {
    this->key = key;
    this->value = value;
}

template<typename T>
int HashTable<T>::hashFunction(int key) const {
    return ((key % size) * (key % size)) % size;
}

template<typename T>
HashTable<T>::HashTable(int size) {
    table = new QStack<Item<T>>[size];
    this->size = size;
}

template<typename T>
HashTable<T>::~HashTable() {}

template<typename T>
void HashTable<T>::insert(int key, T value) {
    int index = hashFunction(key);
    if(get(key) == "dog") table[index].push(Item(key, value));
    else {
        QStack<Item<T>> tempStack;

        while (!table[index].isEmpty()) {
            Item stackItem = table[index].pop();
            tempStack.push((stackItem.key == key) ? (Item<T>(key, value)) : stackItem);

            if (stackItem.key == key) break;
        }

        while (!tempStack.isEmpty()) {
            table[index].push(tempStack.pop());
        }
    }
}

template<typename T>
T HashTable<T>::get(int key) {
    T foundedValue;
    bool isFounded = false;

    int index = hashFunction(key);
    QStack<Item<T>> tempStack;

    while (!table[index].isEmpty()) {
        Item stackItem = table[index].pop();
        tempStack.push(stackItem);
        if (stackItem.key == key) {
            foundedValue = stackItem.value;
            isFounded = true;
            break;
        }
    }

    while (!tempStack.isEmpty()) {
        table[index].push(tempStack.pop());
    }

    return isFounded ? foundedValue : "dog";
}


template<typename T>
void HashTable<T>::remove(int key) {
    int index = hashFunction(key);
    QStack<Item<T>> tempStack;

    while (!table[index].isEmpty()) {
        Item stackItem = table[index].pop();

        if (stackItem.key != key) {
            tempStack.push(stackItem);
        }
    }

    while (!tempStack.isEmpty()) {
        table[index].push(tempStack.pop());
    }

}
