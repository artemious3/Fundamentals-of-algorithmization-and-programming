#include "hashtable.h"
template <typename T>
HashTable<T>::HashTable(int size, int prime) : size(size), p(prime) {
    table.resize(size);
    srand(time(0));
    a = rand() % (p - 1) + 1;
    b = rand() % p;
}

template <typename T>
HashTable<T>::~HashTable() {
    table.resize(0);
}

template <typename T>
int HashTable<T>::hashFunction(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % p;
    }
    return ((a * hash + b) % p) % size;
}

template <typename T>
void HashTable<T>::insert(const std::string& key, T value) {
    int originalIndex = hashFunction(key);
    int index = originalIndex;
    int step = 0;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            table[index].value = value;
            return;
        }
        index = (originalIndex + ++step) % size;

        if (index == originalIndex)
            resize();
    }

    table[index] = Item<T>(key, value);
}

template <typename T>
T HashTable<T>::search(const std::string &key)  {
    int originalIndex = hashFunction(key);
    int index = originalIndex;
    int step = 0;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            return table[index].value;
        }
        index = (originalIndex + ++step) % size;
        if (index == originalIndex) {
            return INT_MAX;
        }
    }
    return INT_MAX;
}

template <typename T>
void HashTable<T>::remove(const std::string& key) {
    int originalIndex = hashFunction(key);
    int index = originalIndex;
    int step = 0;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            table[index].isOccupied = false;
            table[index].clear();
            return;
        }
        index = (originalIndex + ++step) % size;
        if (index == originalIndex) {
            throw std::invalid_argument("Key not found in hash table");
        }
    }
    throw std::invalid_argument("Key not found in hash table");
}

template<typename T>
void HashTable<T>::print(QListWidget *listWidget)
{
    listWidget->clear();

    QString oneStack;

    for(int i = 0; i < this->size; i++)
    {
        oneStack = QString::number(i) + ". ";

        Item stackItem = this->table[i];
        oneStack += QString::fromStdString(stackItem.key) + "(" + QString::number(stackItem.value) + ") ";


        listWidget->addItem(oneStack);
    }
}

template<typename T>
void HashTable<T>::clear()
{
    for(int i = 0; i < this->size; i++)
    {
        table[i] = Item<T>();
    }
}

template <typename T>
void HashTable<T>::resize() {
    std::vector<Item<T>> oldTable = table;
    size *= 2;
    table.clear();
    table.resize(size);

    for (const auto& item : oldTable) {
        if (item.isOccupied) {
            insert(item.key, item.value);
        }
    }
}
