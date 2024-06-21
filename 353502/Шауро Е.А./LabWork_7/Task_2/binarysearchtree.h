#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "node.h"
#include <QString>

class BinarySearchTree {
 public:
  Node* root;
  QString stroka;
  BinarySearchTree();

  void insert(int key, QString value);
  void remove(int key);
  int leftNodesCounter(Node* node);
  void balanceTree();
  QString find(int key);
  QString printPreOrder();
  QString printInOrder();
  QString printPostOrder();

 private:
  Node* insert(Node* root, int key, QString value);
  Node* find(Node* node, int key);
  Node* remove(Node* node, int key);
  Node* findMin(Node* node);
  void balance(Node* node);
  void swap(Node* node1, Node* node2);
  void rightRot(Node* node);
  void leftRot(Node* node);
  void updateHeight(Node* node);
  int getHeight(Node* node);
  int getBalance(Node* node);
  void preOrderHelper(Node* node);  // Прямой обход
  QString inOrder(Node* node);    // Симметричный обход
  QString postOrder(Node* node);  // Обратный обход
};

#endif  // BINARYSEARCHTREE_H
