#include "derivedhashtable.h"
#include <climits>

DerivedHashTable::DerivedHashTable(int size) : HashTable(size) {}

int DerivedHashTable::findMaxStack() {
    int maxIndex = -1; // Инициализация индекса стека с максимальным значением
    int maxValue = INT_MIN; // Инициализация максимального значения

    // Проходим по всем стекам в хеш-таблице
    for (int i = 0; i < size(); ++i) {
        std::stack<int>& tempStack = table[i]; // Временный стек для проверки элементов
        // Проверяем все элементы в текущем стеке
        while (!tempStack.empty()) {
            int top = tempStack.top(); // Получаем верхний элемент стека
            tempStack.pop(); // Удаляем верхний элемент из временного стека
            // Если найденное значение больше текущего максимального, обновляем максимум
            if (top > maxValue) {
                maxValue = top;
                maxIndex = i; // Обновляем индекс стека с максимальным значением
            }
        }
    }

    return maxIndex; // Возвращаем индекс стека с максимальным значением
}
