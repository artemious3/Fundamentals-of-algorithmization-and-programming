#include "queue.h"

Queue::Queue() : first(nullptr), last(nullptr), cur(nullptr), size(0) {}

Queue::~Queue() {
  Node* current = first;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

void Queue::enqueue(int value) {
  Node* newOne = new Node(value);
  if (!first) {
    first = last = newOne;
  } else {
    last->next = newOne;
    newOne->prev = last;
    last = newOne;
  }
  ++size;
}

void Queue::dequeue() {
  if (!first) {
    throw std::runtime_error("Queue is empty");
  }

  Node* temp = first;
  first = first->next;
  if (first) {
    first->prev = nullptr;
  } else {
    last = nullptr;
  }
  delete temp;
  size--;
}

void Queue::goNext() {
  if (!first) {
    throw std::runtime_error("Queue is empty");
  }
  if (!cur->next) {
    throw std::runtime_error("Вы достигли последнего элемента");
  }
  cur = cur->next;
}

void Queue::goPrev() {
  if (!first) {
    throw std::runtime_error("Queue is empty");
  }
  if (!cur->prev) {
    throw std::runtime_error("Это первый элемент");
  }
  cur = cur->prev;
}

int Queue::getCurElement() {
  if (!first) {
    throw std::runtime_error("Queue is empty");
  }
  return cur->data;
}

void Queue::convertToCircular() {
  if (!first) {
    throw std::runtime_error("Queue is empty");
  }
  last->next = first;
  first->prev = last;
}

int Queue::getSize() const {
  return size;
}
