#include "stack.h"

template <typename T>
Stack<T>::Stack() : top(-1) {}

template <typename T>
bool Stack<T>::isEmpty() const {
  return top == -1;
}

template <typename T>
bool Stack<T>::isFull() const {
  return top == MAX_SIZE - 1;
}

template <typename T>
void Stack<T>::push(const T& item) {
  if (isFull()) {
    throw std::runtime_error("Stack overflow");
  }
  data[++top] = item;
}

template <typename T>
T Stack<T>::pop() {
  if (isEmpty()) {
    throw std::runtime_error("Stack underflow");
  }
  return data[top--];
}

template <typename T>
T& Stack<T>::at(int index) {
  if (index < 0 || index > top) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

template <typename T>
int Stack<T>::getSize() const {
  return top + 1;
}

template <typename T>
void Stack<T>::clear() {
  top = -1;
}

template <typename T>
T Stack<T>::peek() const {
  if (isEmpty()) {
    throw std::runtime_error("Stack underflow");
  }
  return data[top];
}
