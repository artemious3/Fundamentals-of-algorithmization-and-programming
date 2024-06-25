#ifndef NODE_H
#define NODE_H
#include <QString>

struct Data {
  int id;
  QString info;
};

class Node {
 public:
  Data data;
  int key;
  int height = 0;
  QString value;

  Node* left;
  Node* right;
  explicit Node(Data dat);
  void swapNodes(Node* a, Node*b);
};

#endif  // NODE_H
