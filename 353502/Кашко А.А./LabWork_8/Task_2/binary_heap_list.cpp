#include "binary_heap_list.h"
#include <iostream>
#include <queue>

BinaryHeapList::BinaryHeapList() : root(nullptr), heapSize(0) {} // Конструктор класса, инициализирует корень кучи и размер кучи нулевыми значениями

void BinaryHeapList::insert(int value) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(value); // Создание нового узла с заданным значением и умным указателем на него
    if (!root) { // куча пустая
        root = newNode;
    } else {
        std::queue<std::shared_ptr<Node>> q; // Создание очереди для обхода дерева
        q.push(root); // Помещение корня в очередь
        while (!q.empty()) { // Пока очередь не пуста
            std::shared_ptr<Node> currentNode = q.front(); // Получение первого элемента из очереди
            q.pop(); // Удаление первого элемента из очереди
            if (!currentNode->left) { // Если у текущего узла нет левого потомка
                currentNode->left = newNode; // Новый узел становится левым потомком
                newNode->parent = currentNode; // Установка родителя для нового узла
                break; // Выход из цикла
            } else if (!currentNode->right) { // Если у текущего узла нет правого потомка
                currentNode->right = newNode; // Новый узел становится правым потомком
                newNode->parent = currentNode; // Установка родителя для нового узла
                break; // Выход из цикла
            } else { // Если у текущего узла есть оба потомка
                q.push(currentNode->left); // Добавление левого потомка в очередь
                q.push(currentNode->right); // Добавление правого потомка в очередь
            }
        }
        siftUp(newNode); // Просеивание нового узла вверх для поддержания свойства кучи
    }
    heapSize++; // Увеличение размера кучи
}

int BinaryHeapList::extractMax() {
    if (!root) {
        return -1; // Куча пуста
    }
    int max = root->value; // Сохраняем значение корня

    if (heapSize == 1) {
        root.reset(); // Если в куче только один элемент, сбрасываем корень (удаляем его из кучи)
    } else {
        std::shared_ptr<Node> lastNode = getLastNode(); // Получаем последний узел кучи

        if (lastNode->parent.lock()) { // Если у последнего узла есть родитель
            if (lastNode->parent.lock()->left == lastNode) { // Если последний узел является левым потомком своего родителя
                lastNode->parent.lock()->left.reset(); // Удаляем ссылку на левого потомка у родителя
            } else {
                lastNode->parent.lock()->right.reset(); // Удаляем ссылку на правого потомка у родителя
            }
        }

        root->value = lastNode->value; // Заменяем значение корня на значение последнего узла
        siftDown(root); // Выполняем просеивание вниз для восстановления свойства кучи
    }

    heapSize--; // Уменьшаем размер кучи
    return max; // Возвращаем сохраненное максимальное значение
}

std::shared_ptr<Node> BinaryHeapList::getLastNode() {
    std::queue<std::shared_ptr<Node>> q; // Создаем очередь для обхода в ширину
    q.push(root); // Помещаем корень кучи в очередь
    std::shared_ptr<Node> lastNode; // Объявляем переменную для хранения последнего узла

    while (!q.empty()) { // Пока очередь не пуста
        lastNode = q.front(); // Получаем элемент из начала очереди (первый элемент на текущем уровне)
        q.pop(); // Удаляем элемент из очереди

        if (lastNode->left) { // Если у текущего узла есть левый потомок
            q.push(lastNode->left); // Добавляем левого потомка в очередь для дальнейшего обхода
        }
        if (lastNode->right) { // Если у текущего узла есть правый потомок
            q.push(lastNode->right); // Добавляем правого потомка в очередь для дальнейшего обхода
        }
    }

    return lastNode; // Возвращаем последний узел, который станет последним извлеченным из очереди (это будет последний узел в обходе в ширину)
}

int BinaryHeapList::getMax() {
    if (!root) {
        return -1;
    }
    return root->value;
}

bool BinaryHeapList::isEmpty() {
    return heapSize == 0;
}

size_t BinaryHeapList::size() {
    return heapSize;
}

void BinaryHeapList::siftUp(std::shared_ptr<Node> node) { // Метод просеивания вверх
    while (node->parent.lock() && node->parent.lock()->value < node->value) { // Пока у узла есть родитель и значение родителя меньше значения узла
        std::swap(node->parent.lock()->value, node->value); // Меняем местами значения узла и его родителя
        node = node->parent.lock(); // Переходим к родителю
    }
}

void BinaryHeapList::siftDown(std::shared_ptr<Node> node) { // Метод просеивания вниз
    while (true) { // Бесконечный цикл
        std::shared_ptr<Node> maxNode = node; // Установка максимального узла в текущий узел
        if (node->left && node->left->value > maxNode->value) { // Если у узла есть левый потомок и его значение больше значения максимального узла
            maxNode = node->left; // Устанавливаем левого потомка как максимальный узел
        }
        if (node->right && node->right->value > maxNode->value) { // Если у узла есть правый потомок и его значение больше значения максимального узла
            maxNode = node->right; // Устанавливаем прав
        }
        if (maxNode != node) { // Если максимальный узел отличается от текущего узла
            std::swap(node->value, maxNode->value); // Меняем местами значения текущего узла и максимального узла
            node = maxNode; // Устанавливаем текущий узел равным максимальному узлу
        } else { // Иначе
            break; // Выходим из цикла
        }
    }
}
