#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.h"

template <class T>
class Iterator {

 public:
  Node<T>* cur;
  unsigned int index;

  Iterator(Node<T>* node, unsigned int index) : cur(node), index(index) {}

  Iterator& operator++() {
    if (cur != nullptr) {
      if (index == cur->last) {
        cur = cur->next;
        index = cur->first;
      } else {
        ++index;
      }
    }
    return *this;
  }

  Iterator& operator--(int) {
    if (cur != nullptr) {
      if (index == cur->first) {
        cur = cur->prev;
        index = cur->last;
      } else {
        --index;
      }
    }
    return *this;
  }

  T& operator*(){
      return cur->node[index];
  }

  bool operator==(const Iterator& other)const{
      return other.cur == cur && other.index == index;
  }

  bool operator!=(const Iterator& other)const{
      return other.cur != cur && other.index != index;
  }

};

#endif  // ITERATOR_H
