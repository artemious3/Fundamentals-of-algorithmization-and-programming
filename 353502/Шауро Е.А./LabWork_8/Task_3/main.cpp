#include <iostream>
#include "HashTable.h"  // Ваш заголовочный файл

int main() {
    // Создаем хеш-таблицу для хранения int как ключей и QString как значений
    HashTable<int, QString> hashTable;

    // Вставляем элементы в хеш-таблицу
    hashTable.insert(HashTable<int, QString>::Pair{1, "One", false});
    hashTable.insert(HashTable<int, QString>::Pair{2, "Two", false});
    hashTable.insert(HashTable<int, QString>::Pair{3, "Three", false});

    // Демонстрация оператора []
    std::cout << "hashTable[1]: " << hashTable[0].toStdString().c_str() << std::endl;

    // Проверка наличия элемента
    int keyToFind = 2;
    if (hashTable.contains(keyToFind)) {
        std::cout << "Element with key " << keyToFind << " is present." << std::endl;
    } else {
        std::cout << "Element with key " << keyToFind << " is not present." << std::endl;
    }

    // Удаление элемента
    int keyToRemove = 3;
    int removedIndex = hashTable.removeByKey(keyToRemove);
    if (removedIndex != -1) {
        std::cout << "Element with key " << keyToRemove << " was removed." << std::endl;
    } else {
        std::cout << "Element with key " << keyToRemove << " was not found or already removed." << std::endl;
    }

    // Попытка доступа к удаленному элементу
    try {
        std::cout << "hashTable[3]: " << hashTable[3].toStdString().c_str() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Очистка хеш-таблицы
    hashTable.clear();
    std::cout << "HashTable cleared." << std::endl;

    // Попытка доступа к элементам после очистки
    try {
        std::cout << "hashTable[1]: " << hashTable[1].toStdString().c_str() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
