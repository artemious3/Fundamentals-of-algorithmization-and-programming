#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QDebug>
#include <QPair>
#include <QVector>
#include <QString>

class HashTable
{
protected:
    int capacity = 1; // Емкость (размер) хеш-таблицы, по умолчанию 1
    QVector<QPair<QString, int>> table; // Вектор пар (ключ, значение), представляющий хеш-таблицу
    QVector<int> collisionHashValues; // Вектор значений хешей, используемый для отслеживания коллизий
    int siseElements = 0;

public:    
    // Конструктор класса HashTable, принимающий размер хеш-таблицы
    HashTable(int size)
    {
        capacity = size; // Устанавливаем емкость хеш-таблицы
        table.resize(capacity); // Изменяем размер вектора table до размера capacity
        collisionHashValues.resize(capacity, -1); // Инициализируем вектор collisionHashValues значениями -1

        // Заполняем вектор table парами (пустая строка, 0) для всех элементов
        for (int i = 0; i < capacity; ++i)
        {
            table[i] = QPair<QString, int>("", 0);
        }
    }

    // Метод получения значений коллизий
    QVector<int> getCollisionHashValues() const {
        return collisionHashValues; // Возвращаем вектор значений коллизий
    }

    // Хеш-функция, вычисляющая индекс для ключа
    int hashFunction(const QString& key)
    {
        long long hash = 0; // Инициализируем переменную для хранения хеша
        for (int i = 0; i < key.size(); ++i) { // Цикл по символам ключа
            hash = hash * 997 + key[i].unicode(); // Добавляем Юникод каждого символа к хешу
            hash %= capacity;
        }
        return hash; // Возвращаем остаток от деления хеша на размер таблицы
    }

    // Метод вставки элемента в хеш-таблицу
    void insertItem(const QString& key, int data)
    {
        int index = hashFunction(key); // Вычисляем индекс с помощью хеш-функции

        // Пока в текущей ячейке таблицы уже есть данные
        while (!table[index].first.isEmpty())
        {
            index = (index + 1) % capacity; // Используем линейное пробирование для поиска следующей свободной ячейки
        }

        // Вставляем ключ и данные в найденную пустую ячейку
        table[index].first = key;
        table[index].second = data;
        siseElements++;

        // Если для этого индекса еще не был записан хеш коллизии
        if (collisionHashValues[index] == -1) {
            collisionHashValues[index] = hashFunction(key); // Записываем хеш коллизии
        }

        if (siseElements > capacity * 0.7) rehash();
    }

    // Метод поиска элемента в хеш-таблице по ключу
    int searchItem(const QString& key) {
        int index = hashFunction(key); // Вычисляем индекс для поиска элемента
        int originalIndex = index; // Сохраняем изначальный индекс для обнаружения циклического обхода

        // Пока ключ в текущей ячейке не совпадает с заданным ключом
        while (table[index].first != key) {
            // Если ячейка пуста или мы вернулись к изначальному индексу - элемент не найден
            if (table[index].first.isEmpty() || index == originalIndex - 1) {
                return -1; // Возвращаем -1, чтобы показать, что элемент не найден
            }
            index = (index + 1) % capacity; // Пробуем следующую ячейку
        }

        return table[index].second; // Возвращаем данные, связанные с найденным ключом
    }

    // Метод для отображения содержимого хеш-таблицы
    QVector<QPair<QString, int>> displayHash()
    {
        QVector<QPair<QString, int>> ans; // Создаем вектор для хранения пар ключ-значение

        // Проходим по всем ячейкам таблицы
        for (int i = 0; i < capacity; i++)
        {
            ans.push_back(table[i]); // Добавляем текущую пару ключ-значение в вектор
        }

        return ans; // Возвращаем вектор с содержимым хеш-таблицы
    }

    void rehash() {
        int oldCapacity = capacity; // Сохраняем старую емкость
        capacity *= 2; // Увеличиваем емкость в 2 раза

        QVector<QPair<QString, int>> oldTable = table; // Сохраняем старую таблицу
        QVector<int> oldCollisionHashValues = collisionHashValues; // Сохраняем старые значения коллизий

        table.clear(); // Очищаем текущую таблицу
        table.resize(capacity); // Изменяем размер текущей таблицы до новой емкости
        collisionHashValues.clear(); // Очищаем текущие значения коллизий
        collisionHashValues.resize(capacity, -1); // Изменяем размер вектора коллизий до новой емкости и инициализируем значениями -1

        // Перехешируем все существующие элементы в новую таблицу
        for (int i = 0; i < oldCapacity; ++i) { // Проходим по всем элементам старой таблицы
            if (!oldTable[i].first.isEmpty()) { // Если ячейка не пуста
                int index = hashFunction(oldTable[i].first); // Вычисляем новый индекс с помощью хеш-функции
                while (!table[index].first.isEmpty()) { // Пока текущая ячейка не пуста
                    index = (index + 1) % capacity; // Используем линейное пробирование для поиска следующей свободной ячейки
                }
                table[index] = oldTable[i]; // Копируем элемент в новую таблицу
                collisionHashValues[index] = hashFunction(oldTable[i].first); // Записываем хеш коллизии
            }
        }
    }

};

#endif // HASHTABLE_H // Конец условной компиляции
