#ifndef DEQUE_H
#define DEQUE_H

#include "Iterator.h"
#include "Node.h"

template <typename T>
class Deque {

 public:
  Node<T>* firstNode;
  Node<T>* lastNode;
  unsigned int size;

  Deque() : firstNode(nullptr), lastNode(nullptr), size(0) {}

  bool isEmpty() { return size == 0; }

  unsigned int getSize() const { return size; }

  Iterator<T> begin() {
      if (isEmpty()) {
        return Iterator<T>(nullptr, 0);
      } else {
        return Iterator<T>(firstNode, firstNode->first);
      }
    }

    Iterator<T> end() {
      if (isEmpty()) {
        return Iterator<T>(nullptr, 0);
      } else {
        return Iterator<T>(lastNode, size);
      }
    }

  // возможно м ожно записать через другие ифы
  void push_back(const T& value) {
      if (lastNode == nullptr || lastNode->last == 3) {
          Node<T>* node = new Node<T>();
          if (isEmpty()) {
              lastNode = firstNode = node;
              node->next = node;
              node->prev = node;
          } else {
              lastNode->next = node;
              node->prev = lastNode;

              firstNode->prev = node;
              node->next = firstNode;

              lastNode = node;
          }
      } else {
          lastNode->last++;
      }
      lastNode->node[lastNode->last] = value;
      size++;
  }

  void push_front(const T& value) {
      if (firstNode == nullptr || firstNode->first == 0) {
          Node<T>* node = new Node<T>();
          if (isEmpty()) {
              node->node[0] = value;
              node->prev = node;
              node->next = node;
              lastNode = firstNode = node;
          } else {
              node->node[3] = value;
              node->first = 3;
              node->last = 3;

              node->next = firstNode;
              firstNode->prev = node;

              node->prev = lastNode;
              lastNode->next = node;

              firstNode = node;
          }
          size++;
      } else {
          firstNode->first--;
          firstNode->node[firstNode->first] = value;
          size++;
      }
  }

  void pop_back() {

    if (isEmpty()) {
      return;
    }

    --size;

    if (lastNode != nullptr) {
      --lastNode->last;
    }

    if (lastNode != nullptr && lastNode->last == -1) {

      Node<T>* temp = lastNode;
      if (lastNode == firstNode) {  // если состоит из 1-го узла
        firstNode = lastNode = nullptr;
      } else {
        lastNode = lastNode->prev;
        if (lastNode != nullptr) {
          lastNode->next = firstNode;
        }
        firstNode->prev = lastNode;
      }

      delete temp;
    }
  }

  void pop_front() {

    if (isEmpty()) {
      return;
    }
    --size;

    if (firstNode != nullptr) {
      ++firstNode->first;
    }

    if (firstNode != nullptr && firstNode->first == 4) {
      Node<T>* temp = firstNode;
      if (firstNode == lastNode) {
        firstNode = lastNode = nullptr;
      } else {
        firstNode = firstNode->next;
        if (firstNode != nullptr) {
          firstNode->prev = lastNode;
        }
        lastNode->next = firstNode;
      }
      delete temp;
    }
  }

  void clear() {
    while (!isEmpty()) {
      pop_back();
    }
  }
};

#endif  // DEQUE_H
