#include <iostream>
#include "heaplist.h"

int main() {
    HeapList heap;

    // Вставляем элементы в кучу
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(25);

    std::cout << "Pre-order traversal:" << std::endl;
    heap.preOrderPrint(heap.getRoot());
    std::cout << std::endl;

    // Удаляем элементы из кучи
    heap.remove(20);
    heap.remove(15);

    std::cout << "Pre-order traversal after removal:" << std::endl;
    heap.preOrderPrint(heap.getRoot());
    std::cout << std::endl;

    return 0;
}
