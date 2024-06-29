#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
class Stack {
 private:
  static const int MAX_SIZE = 100;
  T data[MAX_SIZE];
  int top;

 public:
  Stack();

  bool isEmpty() const;

  bool isFull() const;

  void push(const T& item);

  T pop();

  T& at(int index);

  int getSize() const;

  void clear();

  T peek() const;
};

#endif  // STACK_H
