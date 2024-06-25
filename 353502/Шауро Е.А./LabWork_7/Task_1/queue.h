#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stdexcept"

class Queue {
 public:
  Node* first;
  Node* last;
  Node* cur;
  Queue();
  ~Queue();

  void enqueue(int value);
  void dequeue();
  void goNext();
  void goPrev();
  int getCurElement();
  void convertToCircular();
  int getSize() const;


private:
  int size;
};

#endif  // QUEUE_H
