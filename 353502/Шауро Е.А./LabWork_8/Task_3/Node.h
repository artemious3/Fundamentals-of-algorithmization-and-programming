#ifndef NODE_H
#define NODE_H
#include <QPair>
#include <memory>
#include "stdexcept"

enum colors { BLACK, RED };

template <typename Key, typename Value>
class Node {

 public:
  Node* left;
  Node* right;
  Node* parent;
  int height = 0;
  QPair<Key, Value> data;
  colors color;

  Node() : left(nullptr), right(nullptr), parent(), data(), color(RED) {}

  Node(Key key, Value value)
      : data(QPair<const Key, Value>(key, value)),
        color(RED),
        parent(nullptr),
        left(nullptr),
        right(nullptr) {}

  void swapNodes(Node* a, Node* b) {
    std::swap(a->data, b->data);
    std::swap(a->color, b->color);
  }

  colors getColor() const {
    try {
      if (!this) {
        throw std::runtime_error("Node is nullptr");
      }
      return this->color;
    } catch (const std::exception& e) {
      // Возвращаем черный цвет в случае исключения
      return BLACK;
    }
  }

  void setColor(const colors& value) { color = value; }
};

#endif  // NODE_H
