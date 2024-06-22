#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <chrono>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Sorts {
public:
    std::vector<int> array;
    std::vector<QGraphicsRectItem*> items;
    Sorts();

    void setSize(int size, QGraphicsScene* scene);
    int getSize() const;
    void heapSort(QGraphicsScene* scene);
    void mergeSort(QGraphicsScene* scene);
    void quickSort(QGraphicsScene* scene);
    void interpolationSort(QGraphicsScene* scene);
    int binsearch(const std::vector<int>& arr, int digit);
    int binpow(int digit, int power, int mod);
    std::vector<int>& getArray();


private:
    int size;
    void heapify(int n, int i, QGraphicsScene* scene);
    void swap(int i, int j, QGraphicsScene* scene);
    void mergeSortRecursive(int left, int right, std::vector<int>& tempArray, QGraphicsScene* scene);
    void merge(int left, int mid, int right, std::vector<int>& tempArray, QGraphicsScene* scene);
    void quickSortRecursive(int low, int high, QGraphicsScene* scene);
    int partition(int low, int high, QGraphicsScene* scene);
    int interpolationSearch(int high, int key);
};

#endif // SORTS_H
