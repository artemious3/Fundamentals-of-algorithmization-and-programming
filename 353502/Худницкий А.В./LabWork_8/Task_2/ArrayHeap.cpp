#include "ArrayHeap.h"
#include <stdexcept>

template<typename T>
ArrayHeap<T>::ArrayHeap()
    : _data(new T[INIT_CAPACITY])
    , _size(0)
    , _capacity(INIT_CAPACITY)
{}

template<typename T>
ArrayHeap<T>::~ArrayHeap() {
    clear();
}

template<typename T>
void ArrayHeap<T>::clear() {
    _size = 0;
}

template<typename T>
void ArrayHeap<T>::push(T value) {
    if (is_full()) {
        grow();
    }
    _data[_size++] = value;
    for (int64_t i = (_size / 2) - 1; i >= 0; i--) {
        heapify(i);
    }
}

template<typename T>
T ArrayHeap<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }

    T max_value = _data[0];
    _data[0] = _data[_size--];
    heapify(0);
    return max_value;
}

template<typename T>
T &ArrayHeap<T>::max() {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return _data[0];
}

template<typename T>
size_t ArrayHeap<T>::size() {
    return _size;
}

template<typename T>
bool ArrayHeap<T>::empty() {
    return _size == 0;
}

template<typename T>
size_t ArrayHeap<T>::heapify(size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < _size && _data[left] > _data[largest]) {
        largest = left;
    }

    if (right < _size && _data[right] > _data[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(_data[index], _data[largest]);
        heapify(largest);
    }

    return largest;
}

template<typename T>
void ArrayHeap<T>::grow() {
    _capacity *= 2;

    std::unique_ptr<T[]> new_data(new T[_capacity]);
    std::copy(_data.get(), _data.get() + _size, new_data.get());
    _data.swap(new_data);
}

template<typename T>
bool ArrayHeap<T>::is_full() {
    return _size == _capacity;
}

template class ArrayHeap<int32_t>;
