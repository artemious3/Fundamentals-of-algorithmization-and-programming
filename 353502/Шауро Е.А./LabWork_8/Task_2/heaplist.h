#ifndef HEAPLIST_H
#define HEAPLIST_H
#include <iostream>
#include <memory>
#include "queue"

struct Node {
  int key;
  std::weak_ptr<Node> parent;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  explicit Node(int k) : key(k) {}
};

class HeapList {
 public:
  HeapList() : root(nullptr) {}

  void insert(int key);
  void remove(int key);
  bool isEmpty() const;
  int getMax() const;
  void clear();
  void preOrderPrint(std::shared_ptr<Node> node) const;
  std::shared_ptr<Node> getRoot() const;

 private:
  std::shared_ptr<Node> root;

  std::shared_ptr<Node> findNode(std::shared_ptr<Node> node, int key);
  void heapifyDown(std::shared_ptr<Node> node);
  void heapifyUp(std::shared_ptr<Node> node);
  std::shared_ptr<Node> getLastNode();
  void removeLastNode();
  void swapValues(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);
};

#endif  // HEAPLIST_H
