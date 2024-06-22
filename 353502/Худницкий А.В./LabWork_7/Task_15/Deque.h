#ifndef DEQUE_H
#define DEQUE_H

#include "Node.h"

class Deque {
public:
    Deque();
    ~Deque();

    void enqueue(int value);
    int dequeue();

    void swapMaxMin();

    int peekFront();
    int peekBack();

    void insertBefore(Node* node, int value);
    void insertAfter(Node* node, int value);
    void remove(Node* node);

    void resize(int newSize, int defaultValue = 0);

    // Методы для 5 задания

    bool isEmpty();
    void clear();

    int getSize();

    void push_back(int value);
    void push_front(int value);
    int pop_back();
    int pop_front();

    Node* head;
    Node* tail;
    int size;
};

#endif // DEQUE_H
