#include "hashtable.h"

HashTable::HashTable(int tableSize) : tableSize(tableSize) {
    // Инициализация вектора стеков заданного размера
    table.resize(tableSize);
}

int HashTable::hashFunction(int key) {
    return key % tableSize; // Возвращает остаток от деления ключа на размер таблицы
}

// Метод вставки элемента в хеш-таблицу
void HashTable::insert(int key, int value) {
    int index = hashFunction(key); // Вычисляем индекс с помощью хеш-функции
    table[index].push(value); // Вставляем значение в соответствующий стек
}

// Метод удаления элемента из хеш-таблицы
void HashTable::remove(int key, int value) {
    int index = hashFunction(key); // Вычисляем индекс с помощью хеш-функции
    std::stack<int> tempStack; // Временный стек для хранения элементов
    bool found = false; // Флаг, указывающий, найден ли элемент для удаления

    // Перемещаем элементы в временный стек, исключая удаляемый элемент
    while (!table[index].empty()) {
        int top = table[index].top(); // Получаем верхний элемент стека
        table[index].pop(); // Удаляем верхний элемент из основного стека
        if (top == value && !found) {
            found = true; // Удаляем только первый найденный элемент
        } else {
            tempStack.push(top); // Перемещаем элемент во временный стек
        }
    }

    // Возвращаем остальные элементы обратно в основной стек
    while (!tempStack.empty()) {
        table[index].push(tempStack.top()); // Возвращаем элемент в основной стек
        tempStack.pop(); // Удаляем элемент из временного стека
    }
}

// Метод для вывода содержимого хеш-таблицы в строку
QString HashTable::print() {
    QString result; // Результирующая строка
    for (int i = 0; i < tableSize; ++i) { // Проходим по всем стекам в таблице
        result += "Stack " + QString::number(i) + ": "; // Добавляем номер стека в строку
        std::stack<int> tempStack = table[i]; // Временный стек для копирования элементов
        while (!tempStack.empty()) { // Проходим по элементам стека
            result += QString::number(tempStack.top()) + " "; // Добавляем элемент в строку
            tempStack.pop(); // Удаляем элемент из временного стека
        }
        result += "\n"; // Переход на новую строку для следующего стека
    }
    return result; // Возвращаем результирующую строку
}

// Метод поиска элемента по ключу
int HashTable::find(int key) {
    int index = hashFunction(key); // Вычисляем индекс для поиска элемента
    if (!table[index].empty()) {
        return table[index].top(); // Возвращаем верхний элемент стека
    } else {
        // Если стек пуст, возвращаем некий флаг, например -1
        return -1;
    }
}

// Метод проверки, пуста ли хеш-таблица
bool HashTable::isEmpty() {
    // Проверяем, все ли стеки пусты
    for (int i = 0; i < tableSize; ++i) {
        if (!table[i].empty()) {
            return false; // Если хотя бы один стек не пуст, возвращаем false
        }
    }
    return true; // Если все стеки пусты, возвращаем true
}

// Метод возвращает количество элементов в хеш-таблице
int HashTable::size() {
    int count = 0; // Инициализируем счетчик
    // Проходим по всем стекам и суммируем количество элементов
    for (int i = 0; i < tableSize; ++i) {
        count += table[i].size();
    }
    return count; // Возвращаем общее количество элементов
}

void HashTable::clear() {
    // Очищаем каждый стек в векторе
    for (int i = 0; i < tableSize; ++i) {
        while (!table[i].empty()) {
            table[i].pop();
        }
    }
}
