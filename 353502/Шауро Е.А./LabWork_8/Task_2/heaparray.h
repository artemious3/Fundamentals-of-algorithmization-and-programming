#ifndef HEAPARRAY_H
#define HEAPARRAY_H

#include <QDebug>
#include <QVector>

class HeapArray {
 public:
  HeapArray();
  void heapSort();
  void insert(int value);
  void remove(int value);
  bool isEmpty() const;
  int getMax() const;
  bool contains(int value);

 private:
  QVector<int> heap;
  void heapifyUp(int index);
  int findElement(int value);
  void heapifyDown(int size, int i);
};

#endif  // HEAPARRAY_H
