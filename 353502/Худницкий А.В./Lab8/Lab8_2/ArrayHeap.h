#ifndef ARRAYHEAP_H
#define ARRAYHEAP_H

#include <cstddef>
#include <memory>

constexpr short INIT_CAPACITY = 16;

template<typename T>
class ArrayHeap {
public:
    ArrayHeap();
    ~ArrayHeap();

    void clear();
    void push(T value);
    T pop();
    T &max();
    size_t size();
    bool empty();

private:
    std::unique_ptr<T[]> _data;
    size_t _size;
    size_t _capacity;

    size_t heapify(size_t index);
    void grow();
    bool is_full();

};

#endif // ARRAYHEAP_H
