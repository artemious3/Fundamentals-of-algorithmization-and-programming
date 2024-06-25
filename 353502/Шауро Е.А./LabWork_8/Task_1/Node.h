#include <utility>

#ifndef NODE_H
#define NODE_H
#include <QString>

class Node {
public:
  QString value;
  int key;
  int height = 0;
  Node* left;
  Node* right;

  explicit Node( int key, QString value)
      : value(std::move(value)), left(nullptr), right(nullptr), key(key) {}

  void swapNodes(Node *a, Node *b)
  {
      std::swap(a->key, b->key);
      std::swap(a->value, b->value);
  }

};

#endif  // NODE_H
