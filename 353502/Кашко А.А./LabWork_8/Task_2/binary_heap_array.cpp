#include "binary_heap_array.h"

BinaryHeapArray::BinaryHeapArray() {} // Конструктор класса, ничего не выполняет

void BinaryHeapArray::insert(int value) { // Метод вставки элемента в кучу
    heap.push_back(value); // Добавление элемента в конец вектора
    siftUp(heap.size()); // Процедура просеивания вверх для восстановления свойства кучи
}

int BinaryHeapArray::extractMax() { // Метод извлечения максимального элемента из кучи
    if (heap.empty()) { // Если куча пуста
        return -1; // Возвращаем -1, можно также выбросить исключение
    }
    int max = heap[0]; // Сохраняем максимальный элемент
    heap[0] = heap.back(); // Заменяем корень кучи последним элементом
    heap.pop_back(); // Удаляем последний элемент
    siftDown(0); // Процедура просеивания вниз для восстановления свойства кучи
    return max; // Возвращаем сохраненный максимальный элемент
}

int BinaryHeapArray::getMax() { // Метод получения максимального элемента из кучи
    if (heap.empty()) {
        return -1;
    }
    return heap[0]; // Корень кучи - максимальный элемент
}

bool BinaryHeapArray::isEmpty() {
    return heap.empty();
}

size_t BinaryHeapArray::size() {
    return heap.size();
}

void BinaryHeapArray::siftUp(int index) { // Метод просеивания вверх
    while (index > 0 && heap[(index - 1) / 2] < heap[index]) { // Пока узел не станет корнем кучи или не удовлетворит свойству кучи
        std::swap(heap[(index - 1) / 2], heap[index]); // Меняем местами родителя и потомка
        index = (index - 1) / 2; // Переходим к родителю
    }
}

void BinaryHeapArray::siftDown(int index) { // Метод просеивания вниз
    size_t maxIndex = index; // Устанавливаем максимальный индекс равным текущему узлу
    size_t leftChild = 2 * index + 1; // Индекс левого потомка
    size_t rightChild = 2 * index + 2; // Индекс правого потомка

    if (leftChild < heap.size() && heap[leftChild] > heap[maxIndex]) { // Если левый потомок существует и больше текущего максимального узла
        maxIndex = leftChild; // Устанавливаем максимальный индекс в индекс левого потомка
    }

    if (rightChild < heap.size() && heap[rightChild] > heap[maxIndex]) { // Если правый потомок существует и больше текущего максимального узла
        maxIndex = rightChild; // Устанавливаем максимальный индекс в индекс правого потомка
    }

    if (index != maxIndex) { // Если максимальный индекс отличается от текущего индекса
        std::swap(heap[index], heap[maxIndex]); // Меняем местами текущий узел и максимальный узел
        siftDown(maxIndex); // Рекурсивно вызываем просеивание вниз для узла, в который перемещено значение текущего узла
    }
}
