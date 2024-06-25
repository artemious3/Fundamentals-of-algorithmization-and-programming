#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>

#include "node.h"
#include "node.cpp"

template <typename T>
class Deque
{
public:
    Deque();
    ~Deque(){};

    void push_back(const T &Item);
    void push_front(const T &Item);
    void pop_back();
    void pop_front();

    int size();
    bool empty();

    void clear();

    T &operator[](int index);

private:
    T* front;
    T* back;

    Node<T>* nodes;

    size_t _capacity;
    size_t _size;
};

#endif // DEQUE_H
