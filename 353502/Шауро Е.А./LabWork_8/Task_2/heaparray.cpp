#include "heaparray.h"

HeapArray::HeapArray() {}

void HeapArray::heapifyDown(int size, int i) {

  int root = i;
  int left = 2 * i + 1;  // левый и правый потомок
  int right = 2 * i + 2;

  if (left < size && heap[left] > heap[root]) {
    root = left;
  }
  if (right < size && heap[right] > heap[root]) {
    root = right;
  }
  if (root != i) {
    std::swap(heap[i], heap[root]);
    heapifyDown(size, root);
  }
}

void HeapArray::heapSort() {
  int size = heap.size();
  for (int i = size / 2 - 1; i >= 0; i--) {  // Построение кучи
    heapifyDown(size, i);
  }

  for (int i = size - 1; i >= 0; i--) {  // Извлечение элементов из кучи
    std::swap(heap[0], heap[i]);
    heapifyDown(i, 0);
  }
}

void HeapArray::insert(int value) {
  heap.push_back(value);
  heapifyUp(heap.size() - 1);
}

void HeapArray::remove(int value) {
  int index = findElement(value);
  if (index == -1) {
    qDebug() << "Element not found in heap!";
    return;
  }
  heap[index] = heap.back();
  heap.pop_back();
  heapifyDown(heap.size(), index);
}

void HeapArray::heapifyUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (heap[index] <= heap[parent]) {
      break;
    }
    std::swap(heap[index], heap[parent]);
    index = parent;
  }
}

int HeapArray::findElement(int value) {
  int first = 0;
  int last = heap.size() - 1;

  int middle = 0;
  while (first <= last) {
    middle = (first + last) / 2;

    if (value == heap[middle]) {
      return middle;
    } else if (heap[value] < heap[middle]) {
      last = middle + 1;
    } else {
      first = middle - 1;
    }
  }
  return -1;
}

bool HeapArray::isEmpty() const {
  return heap.empty();
}

int HeapArray::getMax() const {

  if (!heap.empty()) {
    return heap[0];
  }
  throw std::runtime_error("Heap is empty!");
}

bool HeapArray::contains(int value) {

  return findElement(value) != -1;
}
