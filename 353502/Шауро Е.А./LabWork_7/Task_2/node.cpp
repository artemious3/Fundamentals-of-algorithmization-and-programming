#include "node.h"

Node::Node(Data dat) : data(dat), left(nullptr), right(nullptr) {
  key = data.id;
  value = data.info;
}

void Node::swapNodes(Node *a, Node *b)
{
    std::swap(a->key, b->key);
    std::swap(a->value, b->value);
}
