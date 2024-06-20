#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <stack>
#include <QString>

class HashTable {
public:
    // Конструктор с заданным размером хеш-таблицы
    HashTable(int size);

    // Хеш-функция для вычисления индекса элемента по ключу
    int hashFunction(int key);

    // Метод вставки элемента в хеш-таблицу
    void insert(int key, int value);

    // Метод удаления элемента из хеш-таблицы
    void remove(int key, int value);

    // Метод поиска элемента по ключу
    int find(int key);

    // Метод проверки, пуста ли хеш-таблица
    bool isEmpty();

    // Метод возвращает количество элементов в хеш-таблице
    int size();

    // Метод очищает хеш-таблицу, удаляя все элементы
    void clear();

    // Метод для вывода содержимого хеш-таблицы в строку
    QString print();

public:
    // Вектор стеков для хранения элементов хеш-таблицы
    std::vector<std::stack<int>> table;

    // Размер хеш-таблицы
    int tableSize;
};

#endif // HASHTABLE_H
