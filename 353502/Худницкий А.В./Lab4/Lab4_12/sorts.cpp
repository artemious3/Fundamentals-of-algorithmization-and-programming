#include "sorts.h"
#include <cstdlib>
#include <cmath>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

Sorts::Sorts() {
    size = 0;
}

void Sorts::setSize(int size, QGraphicsScene* scene) {
    scene->clear();
    this->size = size;
    srand(static_cast<unsigned>(time(nullptr)));
    array.clear();
    items.clear();

    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        array.push_back(i - size / 2);
    }

    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        size_t j = rand() % static_cast<size_t>(size);
        std::swap(array[i], array[j]);
    }

    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        QGraphicsRectItem* rectItem = new QGraphicsRectItem(i * 10, 0, 10, 10);
        int height = std::abs(8 * array[i]);
        rectItem->setRect(i * 20, 0, 10, height * (array[i] >= 0 ? -1 : 1));
        scene->addItem(rectItem);
        items.push_back(rectItem);
    }
}

int Sorts::getSize() const {
    return size;
}

std::vector<int>& Sorts::getArray() {
    return array;
}

void Sorts::heapSort(QGraphicsScene* scene) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(size, i, scene);

    for (int i = size - 1; i > 0; i--) {
        swap(0, i, scene);
        heapify(i, 0, scene);
    }
    qDebug() << "HeapSort завершен";
}

void Sorts::heapify(int n, int i, QGraphicsScene* scene) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[l] > array[largest])
        largest = l;

    if (r < n && array[r] > array[largest])
        largest = r;

    if (largest != i) {
        swap(i, largest, scene);

        heapify(n, largest, scene);
    }
}

void Sorts::mergeSort(QGraphicsScene* scene) {
    std::vector<int> tempArray(size);
    mergeSortRecursive(0, size - 1, tempArray, scene);
    qDebug() << "MergeSort завершен";
}

void Sorts::mergeSortRecursive(int left, int right, std::vector<int>& tempArray, QGraphicsScene* scene) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(left, mid, tempArray, scene);
    mergeSortRecursive(mid + 1, right, tempArray, scene);
    merge(left, mid, right, tempArray, scene);
}

void Sorts::merge(int left, int mid, int right, std::vector<int>& tempArray, QGraphicsScene* scene) {
    for (int i = left; i <= right; i++) {
        tempArray[i] = array[i];
    }

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (tempArray[i] <= tempArray[j]) {
            array[k] = tempArray[i];
            i++;
        } else {
            array[k] = tempArray[j];
            j++;
        }
        swap(k, k, scene);
        k++;
    }

    while (i <= mid) {
        array[k] = tempArray[i];
        swap(k, k, scene);
        i++;
        k++;
    }

    while (j <= right) {
        array[k] = tempArray[j];
        swap(k, k, scene);
        j++;
        k++;
    }
}

void Sorts::quickSort(QGraphicsScene* scene) {
    quickSortRecursive(0, size - 1, scene);
    qDebug() << "QuickSort завершен";
}

void Sorts::quickSortRecursive(int low, int high, QGraphicsScene* scene) {
    if (low < high) {
        int pi = partition(low, high, scene);

        quickSortRecursive(low, pi - 1, scene);
        quickSortRecursive(pi + 1, high, scene);
    }
}

int Sorts::partition(int low, int high, QGraphicsScene* scene) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(i, j, scene);
        }
    }
    swap(i + 1, high, scene);
    return (i + 1);
}

void Sorts::interpolationSort(QGraphicsScene* scene) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;

        int loc = interpolationSearch(j, key);

        loc = (loc == -1) ? 0 : loc + 1;

        while (j >= loc) {
            swap(j + 1, j, scene);
            j--;
        }
    }
    qDebug() << "InterpolationSort завершен";
}

int Sorts::interpolationSearch(int high, int key) {
    int low = 0;

    while (low <= high && array[low] <= key && key <= array[high]) {
        if (low == high) {
            if (array[low] == key) return low;
            return -1;
        }

        int pos = low + (((double)(high - low) / (array[high] - array[low])) * (key - array[low]));

        if (array[pos] == key)
            return pos;

        if (array[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

void Sorts::swap(int i, int j, QGraphicsScene* scene) {
    items[i]->setBrush(QBrush(Qt::green));
    items[j]->setBrush(QBrush(Qt::green));

    std::swap(array[i], array[j]);

    auto tempRect = items[i];
    items[i] = items[j];
    items[j] = tempRect;

    for (size_t k = 0; k < static_cast<size_t>(size); ++k) {
        int height = std::abs(8 * array[k]);
        items[k]->setRect(k * 10, 0, 10, height * (array[k] >= 0 ? -1 : 1));
        items[k]->setPos(k * 10, 0);
    }

    scene->update();
    QCoreApplication::processEvents();
    QThread::msleep(15);

    items[i]->setBrush(QBrush(Qt::NoBrush));
    items[j]->setBrush(QBrush(Qt::NoBrush));

    qDebug() << "Swap выполнен";
}

int Sorts::binsearch(const std::vector<int>& arr, int digit) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == digit)
            return mid;
        if (arr[mid] < digit)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int Sorts::binpow(int digit, int power, int mod) {
    long long result = 1;
    digit %= mod;
    if (digit < 0) digit += mod;
    while (power > 0) {
        if (power & 1)
            result = (result * digit) % mod;
        digit = (digit * digit) % mod;
        power >>= 1;
    }
    return result;
}

