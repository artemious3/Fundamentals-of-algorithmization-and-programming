#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
  T node[4];
  int first;
  int last;
  Node* prev;
  Node* next;

  Node() : first(0), last(0), prev(nullptr), next(nullptr) {}// узел единственный и пуст
};

#endif  // NODE_H
